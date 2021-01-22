#include "raslib/raslib.hpp"
#include "raslib/gpio.hpp"

int main(int argc, char* argv[])
{
    Gpio led {"Led"};

    if(!led.setup())
    {
        led.set_pin(21);
        while(true)
        {
            led.output(ON);
            sleep(2000);
            led.output(FF);
            sleep(2000);
        }
    }

    return 0;
}