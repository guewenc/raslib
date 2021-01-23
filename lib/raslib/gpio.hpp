#if !defined(RAS_GPIO)
#define RAS_GPIO

#include "raslib.hpp"

#include <fstream>
#include <string>

namespace rl
{
        /**
         * Gpio class:
         * @brief class to control GPIO pins, can set on/off pins.
         * @details This class is used to modify the file containing the value of the pin. 
         * It will directly create a folder for the selected pin if it does not exist, and modify the file with the value of 0 or 1.
        */
        class Gpio
        {
          public:
            // Constructors
            Gpio();
            Gpio(std::string const);
            Gpio(std::string const, int const);

            // Methods
            int output(int const);

            // Setters
            void set_name(std::string const);
            int set_pin(int const);

            // Getters
            std::string get_name();
            int get_pin();

          private:
            std::string m_name;
            int m_pin;
            bool m_logs;
        };

    // Constructors
    Gpio::Gpio()
    {
        Gpio::m_name = "undefined";
        Gpio::m_pin = 0;
    }

    Gpio::Gpio(std::string const name)
    {
        Gpio::m_name = name;
        Gpio::m_pin = 0;
    }

    Gpio::Gpio(std::string const name, int const pin)
    {
        Gpio::m_name = name;
        Gpio::m_pin = pin;
        Gpio::set_pin(Gpio::m_pin);
    }

    // Methods
    int Gpio::output(int const put)
    {
        // direction:
        std::string const DIR_PATH {GPIO_PATH + "gpio" + std::to_string(Gpio::m_pin) + "/direction"};
    
        std::ofstream dir_file {DIR_PATH, std::ios::out};
        if(dir_file)
        {
            if(logs)
                log(DIR_PATH + " exists", true);

            dir_file << "out";
            dir_file.close();
        }
        else
        {
            dir_file.close();
            return log("Unable to open: " + DIR_PATH, -1, true);
        }

        // gpio:
        std::string const VALUE_PATH {GPIO_PATH + "gpio" + std::to_string(Gpio::m_pin) + "/value"};
    
        std::ofstream value_file {VALUE_PATH, std::ios::out};
        if(value_file)
        {
            if(logs)
                log(VALUE_PATH + " exists", true);

            // check if it's ON or OFF and write in file
            (put) ? value_file << ON : value_file << OFF;
            value_file.close();  

            if(logs)
                log("Pin \"" + Gpio::m_name + "\" (" + std::to_string(Gpio::m_pin) + ") set to " + std::to_string(put));

            return 0;
        }
        else
        {
            value_file.close();
            return log("Unable to open: " + VALUE_PATH, -1, true);
        }
    }

    // Setters
    void Gpio::set_name(std::string const name)
    {
        Gpio::m_name = name;
        if(logs)
            log("Name set to: " + Gpio::m_name);
    }

    int Gpio::set_pin(int const pin)
    {
        Gpio::m_pin = pin;

        // create a folder for the selected pin
        std::ofstream export_file {GPIO_PATH + "export", std::ios::out};
        if(export_file)
        {
            if(logs)
                log(GPIO_PATH + " exists", true);

            export_file << Gpio::m_pin;
            export_file.close();

            if(logs)
                if(Gpio::m_pin == 0)
                    log("Pin \"" + Gpio::m_name + "\" set to UNDEFINED");
                else
                    log("Pin \"" + Gpio::m_name + "\" set to " + std::to_string(Gpio::m_pin));

            return 0;
        }
        else
        {
            export_file.close();
            return log("Unable to open: " + GPIO_PATH + "export", -1, true);;
        }       
    }

    // Getters
    std::string Gpio::get_name()
    {
        return Gpio::m_name;
    }

    int Gpio::get_pin()
    {
        return Gpio::m_pin;
    }

}

#endif