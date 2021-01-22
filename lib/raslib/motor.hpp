#if !defined(RAS_MOTOR)
#define RAS_MOTOR

#include "raslib.hpp"
#include "gpio.hpp"

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
        int output(int const);

        // Setters
        void set_name(std::string const);
        void set_pins(int const, int const, int const);

        // Getters
        std::string get_name();
        int* get_pins();

      private:
        std::string m_name;
        Gpio m_gpio_pins[3];
        int m_pins[3];
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
int Motor::setup()
{
    Gpio null {"null"};
    return null.setup();
}

int Motor::output(int const put)
{
    if(put == ON)
    {
        int res1 {Motor::m_gpio_pins[0].output(ON)};
        int res2 {Motor::m_gpio_pins[1].output(ON)};
        int res3 {Motor::m_gpio_pins[2].output(OFF)};

        // check if all result of the ouput() function are good
        if(res1 == res2 && res2 == res3 && res1 == 0)
            return 0;
        else
            return -1;
    }
    else if(put == OFF)
        return Motor::m_gpio_pins[0].output(OFF);
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
    Motor::m_pins[0] = en;
    Motor::m_pins[1] = a;
    Motor::m_pins[2] = b;

    Gpio en_gpio {Motor::m_name + " EN", Motor::m_pins[0]};
    Gpio a_gpio {Motor::m_name + " A", Motor::m_pins[1]};
    Gpio b_gpio {Motor::m_name + " B", Motor::m_pins[2]};

    Motor::m_gpio_pins[0] = en_gpio;
    Motor::m_gpio_pins[1] = a_gpio;
    Motor::m_gpio_pins[2] = b_gpio;
}

// Getters
std::string Motor::get_name()
{
    return Motor::m_name;
}

int* Motor::get_pins()
{
    return Motor::m_pins;
}

#endif