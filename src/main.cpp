#include "raslib/raslib.hpp"
#include "raslib/gpio.hpp"
#include "raslib/motor.hpp"

int main(int argc, char* argv[])
{
    rl::Motor motor {"Motor"};
    if(!motor.setup(true))
    {
        motor.set_pins(14, 18, 15);
        motor.output(rl::FORWARD);
    }
    
    rl::Motor motor2 {"Motor2"};
    if(!motor.setup(true))
    {
        motor.set_pins(25, 8, 7);
        motor.output(rl::FORWARD);
    }
    
    return 0;
}