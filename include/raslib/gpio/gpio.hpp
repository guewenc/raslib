#if !defined(__RASLIB_GPIO__)
#define __RASLIB_GPIO__

    #include <raslib/raslib.hpp>
    #include <fstream>
    #include <string>

    namespace rs
    {
        std::string const GPIO_PATH {"/sys/class/gpio/"};

        class Gpio
        {
            public:
                Gpio();
                Gpio(int pin);
                void define(int pin);
                void write(int value);
                int get_pin();

            private:
                int m_pin;
                int value;
        };
    }
    
#endif // __RASLIB_GPIO__