#include "raslib/raslib.hpp"

namespace raslib
{
    std::string m_model {""};
    bool m_logs;

    int setup(bool const logs)
    {
        m_logs = logs;

        // check gpio and cpu informations files:
        if(access("/sys/class/gpio/", 0))
            return -1;

        if(access("/proc/cpuinfo", 0))
            return -1;

        // get model:
        std::ifstream cpuinfo_file {"/proc/cpuinfo", std::ios::out};
        if(cpuinfo_file)
        {   
            std::string line {"undefined"};
            bool found_model {false};

            // get the model name of the raspberry, with reading file line per line until found the line contain "Model"
            while(std::getline(cpuinfo_file, line))
            {
                if(line.find("Model") != std::string::npos)
                {
                    found_model = true;
                    m_model = line;

                    // keep only model name, not other informations
                    size_t pos {m_model.find("Model\t\t: ")};
                    (pos != std::string::npos) ? m_model.erase(pos, 9) : m_model = "error";
                    break; // exit the loop
               }
            }

            cpuinfo_file.close();
        }
        else
        {
            cpuinfo_file.close();
            return -1;
        }

        return 0;
    }

    void sleep(int const how_long)
    {
        /**
         * This function was from GPIO Interface Lbrary For The Raspberry Pi : Wiring Pi (http://wiringpi.com/ ; https://github.com/WiringPi/WiringPi)
         * It's an open source library, great thanks to Gordon !
        */
        struct timespec sleeper, dummy;

        sleeper.tv_sec  = static_cast<time_t>(how_long / 1000);
        sleeper.tv_nsec = static_cast<long>((how_long % 1000) * 1000000);
        nanosleep(&sleeper, &dummy) ;
    }
}