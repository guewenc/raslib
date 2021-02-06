#if !defined(__RASLIB_MOTOR__)
#define __RASLIB_MOTOR__

#include "rasgpio.hpp"

namespace raslib
{
    class motor
    {
        public:
            motor();
            motor(std::string const);
            motor(int const, int const, int const);
            motor(std::string const, int const, int const, int const);

            int output(int const);
            int set_pins(int const, int const, int const);
            void set_name(std::string const);

            int* get_pins();
            std::string get_name();

        private:
            std::string m_name;
            raslib::gpio* m_gpio_pins[3];
    };
}

#endif