#include "raslib/rasgpio.hpp"

namespace raslib
{
    gpio::gpio() 
    {
        this->set_name("undefined");
        this->set_pin(-1);
    }

    gpio::gpio(std::string const name)
    {
        this->set_name(name);
        this->set_pin(-1);
    }

    gpio::gpio(int const pin)
    {
        this->set_name("undefined");
        this->set_pin(pin);
    }

    gpio::gpio(std::string const name, int const pin)
    {
        this->set_name(name);
        this->set_pin(pin);
    }


    int gpio::output(bool const value)
    {
        // direction file
        std::ofstream direction_file {(m_GPIO_PATH + "gpio" + std::to_string(m_pin) + "/direction"), std::ios::out};
        if(direction_file)
        {
            direction_file << "out";
            direction_file.close();
        }
        else
        {
            direction_file.close();
            return -1;
        }

        // value file
        std::ofstream value_file {(m_GPIO_PATH + "gpio" + std::to_string(m_pin) + "/value"), std::ios::out};
        if(value_file)
        {
            // check if it's ON or OFF and write in file
            (value) ? value_file << raslib::ON : value_file << raslib::OFF;
            value_file.close();  
        }
        else
        {
            value_file.close();
            return -1;
        }

        return 0;
    }

    int gpio::set_pin(int const pin)
    {
        m_pin = pin;
        if(m_pin > 0)
        {
            // create folder for the pin in the export file
            std::ofstream export_file {m_GPIO_PATH + "export", std::ios::out};
            if(export_file)
            {
                export_file << m_pin;
                export_file.close();
            }
            else 
            { 
                export_file.close();
                return -1;
            }
        }
        else { return -1; }

        return 0;
    }

    void gpio::set_name(std::string const name)
    {
        m_name = name;
    }


    int gpio::get_pin() { return m_pin; }
    std::string gpio::get_name() { return m_name; }
}