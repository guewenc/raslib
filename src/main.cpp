#include "raslib/raslib.hpp"
#include "raslib/gpio.hpp"
#include "raslib/motor.hpp"

int main(int argc, char* argv[])
{
    if(!rl::setup(false))
    {
        rl::Motor motor {"Motor"};
        rl::Motor motor2 {"Motor2"};

        motor.set_pins(14, 18, 15);
        motor2.set_pins(25, 8, 7);
        
        while(true)
        {
            rl::sleep(5000);
            // forward
            motor.output(rl::ON);
            motor2.output(rl::ON);

            rl::sleep(5000);
            // stop
            motor.output(rl::OFF); 
            motor2.output(rl::OFF);
        }
    }
    else
    {
        return rl::log("Setup failed", -1);
    }
    
    return 0;
}