#include "raslib.hpp"

    namespace rs
    {
        void sleep(int const time)
        {
            struct timespec sleeper, dummy;
            sleeper.tv_sec  = static_cast<time_t>(time / 1000);
            sleeper.tv_nsec = static_cast<long>((time % 1000) * 1000000);
            nanosleep(&sleeper, &dummy) ;
        }

        int valid(std::string path)
        {
            if(access(path.c_str(), 0) == -1)
            {
                out("Can't access to '" + path + "' !");
                return -1;
            }
            return 0;
        }

        // setup:
        int setup()
        {
            if(valid("/sys/class/gpio/") == -1)
                return -1;
            if(valid("/proc/cpuinfo") == -1)
                return -1;
            return 0;
        }

        std::string get_model()
        {
            std::ifstream cpuinfo_file {"/proc/cpuinfo", std::ios::out};
            if(cpuinfo_file.is_open())
            {
                std::string line;
                while(std::getline(cpuinfo_file, line))
                {
                    if(line.find("Model") != std::string::npos)
                        break;
                }
                return line.erase(line.find("Model\t\t: "), 9);
            }

            return "NULL";
        }

        // output :
        void __putstr(std::string format)
        {
            for(int i {0}; i < format.length(); i++)
                putchar(format[i]);
        }

        void __reset(bool *start)
        {
            if(*start)
                *start = false;
            else { __putstr("\033[0m"); *start = true; }
        }

        std::string __get_datetime() 
        {
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);

            strftime(buf, sizeof(buf), "%F %X", &tstruct);

            return buf;
        }

        void out(std::string format, ...)
        {
            bool start {true};           
            va_list args;
            va_start(args, format); 

            __putstr(__get_datetime() + " ");
    
            for(int i {0}; i < format.length(); i++)
            {
                // bold
                if(format[i] == '*' && format[i + 1] == '*')
                {
                    format[i] = 0;
                    format[i + 1] = 0;
                    __putstr("\033[1m");
                    __reset(&start);
                }   

                // italic
                if(format[i] == '*' && format[i + 1] != '*')
                {
                    format[i] = 0;
                    __putstr("\033[3m");
                    __reset(&start);
                }

                // variables
                if(format[i] == '$')
                {
                    switch(format[i + 1])
                    {
                        // char
                        case 'c':
                            putchar(static_cast<char>(va_arg(args, int)));
                            break;
                        // integer
                        case 'i':
                            __putstr( std::to_string( va_arg(args, int) ) );
                            break;
                        // float
                        case 'f':
                            __putstr( std::to_string( static_cast<float>(va_arg(args, double)) ) );
                            break;
                        // double
                        case 'd':
                            __putstr( std::to_string( va_arg(args, double) ) );
                            break;
                        // default
                        default:
                            break;
                    }
                    format[i] = 0;
                    format[i + 1] = 0;
                }

                putchar(format[i]);
            }
            putchar('\n');
            va_end(args);
        }
    }
