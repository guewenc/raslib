#if !defined(RAS)
#define RAS

#include <iostream>
#include <string>

    int const ON {1};
    int const OFF {0};

    std::string const GPIO_PATH {"/sys/class/gpio/"};
    std::string const CPUINFO_PATH {"/proc/cpuinfo"};
    std::string model {"undefined"};

    void sleep(int how_long)
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

    int log(std::string const message, int const flow)
    {
        if(flow == -1)
        {
            std::cerr << "\033[0;41m" << "err>ras>" << message << "\033[0m" << std::endl;
            return -1;
        }
        else if(flow == 0)
        {
            std::cout << "\033[0;42m" << "ras>" << "\033[0m " << message << std::endl;
            return 0;
        }
        else
        {
            return 1;
        }
    }

    int log(std::string const message)
    {
        return log(message, 0);
    }

#endif