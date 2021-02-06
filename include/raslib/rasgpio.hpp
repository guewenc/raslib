#if !defined(__RASLIB_GPIO__)
#define __RASLIB_GPIO__

#include "raslib.hpp"

#include <string>
#include <fstream>

namespace raslib
{
    class gpio
    {
        public:
            gpio();
            gpio(std::string const);
            gpio(int const);
            gpio(std::string const, int const);

            int output(bool const);
            int set_pin(int const);
            void set_name(std::string const);
            
            int get_pin();
            std::string get_name();

        private:
            std::string m_name;
            int m_pin;

            std::string const m_GPIO_PATH {"/sys/class/gpio/"};
    };
}

#endif