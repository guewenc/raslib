#if !defined(RAS)
#define RAS

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> // To use the "acess()" function

namespace rl
{
    int const ON {1};
    int const OFF {0};

    int const FORWARD {1};
    int const BACKWARD {-1};
    int const STOP {0};

    bool logs {false};

    std::string const GPIO_PATH {"/sys/class/gpio/"};
    std::string const CPUINFO_PATH {"/proc/cpuinfo"};
    std::string model {"undefined"};

    void sleep(int const how_long)
    {
        /**
         * This function was from GPIO Interface Lbrary For The Raspberry Pi : Wiring Pi (http://wiringpi.com/ ; https://github.com/WiringPi/WiringPi)
         * It's an open source library, great thanks to Gordon !
        */
        struct timespec sleeper, dummy;

        sleeper.tv_sec  = static_cast<time_t>(how_long / 1000);
        sleeper.tv_nsec = static_cast<long>((how_long % 1000) * 1000000);
        nanosleep (&sleeper, &dummy) ;
    }

    int log(std::string const message, int const flow, bool const file)
    {
        if(flow == -1)
        {
            if(file)
                std::cerr << "\033[1;41m" << "err>raslib>" << message << "\033[0m" << std::endl;
            else
                std::cerr << "\033[0;41m" << "err>raslib>" << message << "\033[0m" << std::endl;
            return -1;
        }
        else if(flow == 0)
        {
            if(file)
                std::cout << "\033[1;42m" << "raslib>" << "\033[0m\033[1m " << message << "\033[0m" << std::endl;
            else
                std::cout << "\033[0;42m" << "raslib>" << "\033[0m " << message << std::endl;
            
            return 0;
        }
        else
        {
            return 1;
        }
    }

    int log(std::string const message, bool const file)
    {
        return log(message, 0, file);
    }

    int log(std::string const message, int const flow)
    {
        return log(message, flow, false);
    }

    int log(std::string const message)
    {
        return log(message, 0);
    }

    int setup(bool set_logs)
    {        
        if(set_logs)
            logs = true;

        // check gpio and cpu informations files:
        if(access(GPIO_PATH.c_str(), 0))
            return log("Unable to acess to: " + GPIO_PATH, -1, true);
        else if(logs)
            log(GPIO_PATH + ": acess confirmed", true);

        if(access(CPUINFO_PATH.c_str(), 0))
            return log("Unable to acess to: " + CPUINFO_PATH, -1, true);
        else if(logs)
            log(CPUINFO_PATH + ": acess confirmed", true);

        // get model:
        std::ifstream cpuinfo_file {CPUINFO_PATH, std::ios::out};
        if(cpuinfo_file)
        {
            if(logs)
                log(CPUINFO_PATH + " exists", true);
            
            std::string line {"undefined"};
            bool found_model {false};

            // get the model name of the raspberry, with reading file line per line until found the line contain "Model"
            while(std::getline(cpuinfo_file, line))
            {
                if(line.find("Model") != std::string::npos)
                {
                    found_model = true;
                    model = line;

                    // keep only model name, not other informations
                    size_t pos {model.find("Model\t\t: ")};
                    (pos != std::string::npos) ? model.erase(pos, 9) : model = "error";
                    break; // exit the loop
               }
            }

            cpuinfo_file.close();

            if(!found_model)
               return log("Unable to find the model of Raspberry Pi", -1);
            else if(logs)
                log(rl::model + ": model found");

            return 0;
        }
        else
        {
            return log("Unable to open: " + CPUINFO_PATH, -1, true);
        }
    }
}

#endif