#if !defined(__RASLIB_MOTOR__)
#define __RASLIB_MOTOR__

    #include <raslib/raslib.hpp>
    #include <raslib/gpio/gpio.hpp>
    #include <string>

    namespace rs
    {
        class Motor
        {
            public:
                Motor(std::string name);
                Motor(std::string name, int const EN, int const A, int const B);
                void define(int const EN, int const A, int const B);
                void rename(std::string name);
                void write(int value);
                std::string get_name();
                int *get_pins();

            private:
                std::string m_name;
                Gpio *m_gpios[3];
        };
    }

#endif // __RASLIB_MOTOR__