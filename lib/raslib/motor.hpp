#if !defined(RAS_MOTOR)
#define RAS_MOTOR

#include "raslib.hpp"
#include "gpio.hpp"

namespace rl
{
        /**
         * Motor class:
         * @brief use Gpio Class to control GPIO pins of L298N controller
        */
        class Motor
        {
          public:
            // Constructors
            Motor();
            Motor(std::string const);
            Motor(std::string const, int const, int const, int const);

            // Methods
            int setup();
            int setup(bool);
            int output(int const);

            // Setters
            void set_name(std::string const);
            void set_pins(int const, int const, int const);

            // Getters
            std::string get_name();
            int* get_pins();

          private:
            std::string m_name;
            Gpio* m_gpio_pins[3];
        };

    // Constructors
    Motor::Motor()
    {
        Motor::m_name = "undefined";
        Motor::set_pins(0, 0, 0);
    }

    Motor::Motor(std::string const name)
    {
        Motor::m_name = name;
        Motor::set_pins(0, 0, 0);
    }

    Motor::Motor(std::string const name, int const en, int const a, int const b)
    {
        Motor::m_name = name;
        Motor::set_pins(en, a, b);
    }

    // Methods
    int Motor::setup(bool logs)
    {
        Gpio null {"null"};
        return null.setup(logs);
    }

    int Motor::setup()
    {
        Gpio null {"null"};
        return null.setup(false);
    }

    int Motor::output(int const put)
    {
        if(put == FORWARD)
        {
            int res1 {Motor::m_gpio_pins[0]->output(FORWARD)};
            int res2 {Motor::m_gpio_pins[1]->output(FORWARD)};
            int res3 {Motor::m_gpio_pins[2]->output(STOP)};

            // check if all result of the ouput() function are good
            if(res1 == res2 && res2 == res3 && res1 == 0)
                return 0;
            else
                return -1;
        }
        else if(put == STOP)
            return Motor::m_gpio_pins[0]->output(STOP);
        else
            return 1;
    }

    // Setters
    void Motor::set_name(std::string const name)
    {
        Motor::m_name = name;
    }

    void Motor::set_pins(int const en, int const a, int const b) 
    {
        
        Motor::m_gpio_pins[0] = new Gpio {Motor::m_name + " EN", en};
        Motor::m_gpio_pins[1] = new Gpio {Motor::m_name + " A", a};
        Motor::m_gpio_pins[2] = new Gpio {Motor::m_name + " B", b};;
    }

    // Getters
    std::string Motor::get_name()
    {
        return Motor::m_name;
    }

    int* Motor::get_pins()
    {
        return new int[3] {
            Motor::m_gpio_pins[0]->get_pin(),
            Motor::m_gpio_pins[1]->get_pin(), 
            Motor::m_gpio_pins[2]->get_pin()
        };
    }
}

#endif