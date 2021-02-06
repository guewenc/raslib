#include "raslib/rasmotor.hpp"

namespace raslib
{
    motor::motor() 
    {
        this->set_name("undefined");
        this->set_pins(-1, -1, -1);
    }

    motor::motor(std::string const name)
    {
        this->set_name(name);
        this->set_pins(-1, -1, -1);
    }

    motor::motor(int const en, int const a, int const b)
    {
        this->set_name("undefined");
        this->set_pins(en, a, b);
    }

    motor::motor(std::string const name, int const en, int const a, int const b)
    {
        this->set_name(name);
        this->set_pins(en, a, b);
    }


    int motor::output(int const value)
    {
        if(value == raslib::FORWARD)
        {
            if(m_gpio_pins[0] != NULL)
            {
                int result_1 {m_gpio_pins[0]->output(raslib::ON)};
                int result_2 {m_gpio_pins[1]->output(raslib::ON)};
                int result_3 {m_gpio_pins[2]->output(raslib::OFF)};

                // check if all result of the ouput() method are good
                if(result_1 = 0 && result_2 == 0 && result_3 == 0) { return 0; }
                else { return -1; }
            }
            else { return -1; }
        }
        else if(value == raslib::STOP) 
        { 
            return m_gpio_pins[0]->output(raslib::OFF); 
        }
        else { return 1; }

        return 0;
    }

    int motor::set_pins(int const en, int const a, int const b) 
    {
        if(en > 0 && a > 0 && b > 0)
        {
            m_gpio_pins[0] = new raslib::gpio {m_name + " EN", en};
            m_gpio_pins[1] = new raslib::gpio {m_name + " A", a};
            m_gpio_pins[2] = new raslib::gpio {m_name + " B", b};;
        }
        else { return -1; }

        return 0;
    }

    void motor::set_name(std::string const name)
    {
        m_name = name;
    }


    int* motor::get_pins()
    {         
        return new int[3] {
            motor::m_gpio_pins[0]->get_pin(),
            motor::m_gpio_pins[1]->get_pin(), 
            motor::m_gpio_pins[2]->get_pin()
        }; 
    }

    std::string motor::get_name() { return m_name; }
}