#include "raslib/raslib.hpp"
#include "raslib/rasgpio.hpp"

int main(int argc, char* argv[])
{
    raslib::gpio blue_led {"Blue led"};

    if(!raslib::setup(raslib::NO_LOGS))
    {
        blue_led.set_pin(7);
        blue_led.output(raslib::ON);
    }
    else { return -1; }

    return 0;
}
