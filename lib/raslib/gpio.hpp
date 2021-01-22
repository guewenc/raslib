#if !defined(RAS_GPIO)
#define RAS_GPIO

#include "raslib.hpp"

#include <fstream>
#include <string>
#include <unistd.h> // To use the "acess()" function

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
        int setup();
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
int Gpio::setup()
{
    // check gpio and cpu informations files:
    if(access(GPIO_PATH.c_str(), 0))
        return log("Unable to acess to: " + GPIO_PATH, -1);

    if(access(CPUINFO_PATH.c_str(), 0))
        return log("Unable to acess to: " + CPUINFO_PATH, -1);

    // get model:
    std::ifstream cpuinfo_file {CPUINFO_PATH, std::ios::out};
    if(cpuinfo_file)
    {
        std::string line {"undefined"};
        bool found_model {false};

        // get the model name of the raspberry, with reading file line per line until found the line contain "Model"
        while(std::getline(cpuinfo_file, line))
        {
            if(line.find("Model") != std::string::npos)
            {
                found_model = true;
                model = line;

                // keep only model name, not other informations
                size_t pos {model.find("Model\t\t: ")};
                (pos != std::string::npos) ? model.erase(pos, 9) : model = "error";
                break; // exit the loop
            }
        }

        cpuinfo_file.close();

        if(!found_model)
            return log("Unable to find the model of Raspberry Pi", -1);

        return 0;
    }
    else
    {
        return log("Unable to open: " + CPUINFO_PATH, -1);
    }
}

int Gpio::output(int const put)
{
    // direction:
    std::string const DIR_PATH {GPIO_PATH + "gpio" + std::to_string(Gpio::m_pin) + "/direction"};
    
    std::ofstream dir_file {DIR_PATH, std::ios::out};
    if(dir_file)
    {
        dir_file << "out";
        dir_file.close();
    }
    else
    {
        dir_file.close();
        return log("Unable to open: " + DIR_PATH, -1);
    }

    // gpio:
    std::string const VALUE_PATH {GPIO_PATH + "gpio" + std::to_string(Gpio::m_pin) + "/value"};
    
    std::ofstream value_file {VALUE_PATH, std::ios::out};
    if(value_file)
    {
        // check if it's ON or OFF and write in file
        (put) ? value_file << ON : value_file << OFF;
        value_file.close();  
        return 0;
    }
    else
    {
        value_file.close();
        return log("Unable to open: " + VALUE_PATH, -1);
    }
}

// Setters
void Gpio::set_name(std::string const name)
{
    Gpio::m_name = name;
}

int Gpio::set_pin(int const pin)
{
    Gpio::m_pin = pin;

    // create a folder for the selected pin
    std::ofstream export_file {GPIO_PATH + "export", std::ios::out};
    if(export_file)
    {
        export_file << Gpio::m_pin;
        export_file.close();

        return 0;
    }
    else
    {
        export_file.close();
        return log("Unable to open: " + GPIO_PATH + "export", -1);;
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

#endif