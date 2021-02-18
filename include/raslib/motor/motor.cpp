#include "motor.hpp"

namespace rs
{
    Motor::Motor(std::string name)
    {
        this->rename(name);
    }

    Motor::Motor(std::string name, int const EN, int const A, int const B)
    {
        this->rename(name);
        this->define(EN, A, B);
    }

    void Motor::define(int const EN, int const A, int const B)
    {
        if(EN > 0 && A > 0 && B > 0)
        {
            this->m_gpios[0] = new Gpio {EN};
            this->m_gpios[1] = new Gpio {A};
            this->m_gpios[2] = new Gpio {B};
        }
        else
        {
            out("Please choose 3 numbers between 2 and 27 included");
            return;
        }
    }

    void Motor::rename(std::string name)
    {
        if(!name.empty())
            this->m_name = name;
        else
            out("Name can't be empty !");
    }

    void Motor::write(int value)
    {
        if(value == FORWARD)
        {
            if(this->m_gpios[0] != 0)
            {
                this->m_gpios[0]->write(ON);
                this->m_gpios[1]->write(ON);
                this->m_gpios[2]->write(OFF);
            }
        }
        else if(value == OFF)
            this->m_gpios[0]->write(OFF);
        else if(value == BACKWARD)
            out("Sorry, this version of raslib do not support backward !");
        else
            out("Value must be FORWARD, BACKWARD or OFF (1, 2 or 0) !");
    }

    std::string Motor::get_name()
    {
        if(this->m_name != "")
            return this->m_name;
        return "NULL";
    }

    int *Motor::get_pins()
    {
        return new int[3]
        {
            this->m_gpios[0]->get_pin(),
            this->m_gpios[1]->get_pin(), 
            this->m_gpios[2]->get_pin()        
        };
    }
}