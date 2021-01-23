#if !defined(RAS)
#define RAS

#include <iostream>
#include <string>

namespace rl
{
    int const ON {1};
    int const OFF {0};

    int const FORWARD {1};
    int const BACKWARD {-1};
    int const STOP {0};

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
}

#endif