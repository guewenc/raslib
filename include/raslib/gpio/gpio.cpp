#include "gpio.hpp"

namespace rs 
{
    Gpio::Gpio() {}
    Gpio::Gpio(int pin)
    {
        this->define(pin);
    }

    void Gpio::define(int pin)
    {
        if(pin >= 2 && pin <= 27)
            this->m_pin = pin;
        else
        {
            out("Pin $i is not a GPIO pin, please choose a number between 2 and 27 included", pin);
            return;
        }

        std::ofstream export_file {GPIO_PATH + "export", std::ios::out};
        if(export_file.is_open())
            export_file << this->get_pin();
        else
        {
            out("Can't open export file !");
            return;
        }
        export_file.close();
    }

    void Gpio::write(int value)
    {
        std::ofstream direction_file {GPIO_PATH + "gpio" + std::to_string(this->get_pin()) + "/direction",
                                      std::ios::out};
        if(direction_file)
            direction_file << "out";
        else
        {
            out("Can't open direction file !");
            return;
        }
        direction_file.close();

        std::ofstream value_file {GPIO_PATH + "gpio" + std::to_string(this->get_pin()) + "/value",
                                 std::ios::out};
        if(value_file)
        {
            if(value == ON || value == OFF)
                value_file << value;
            else
            {
                out("Value must be ON or OFF (1 or 0) !");
                return;
            }
        }
        else
        {
            out("Can't open value file !");
            return;
        }
        value_file.close();
    }

    int Gpio::get_pin()
    {
        if(this->m_pin != 0)
            return this->m_pin;
        return 0; // NULL PIN
    }
}