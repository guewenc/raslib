#include <raslib/gpio/gpio.hpp>
#include <raslib/motor/motor.hpp>
#include <raslib/socket/socket.hpp>

int main(int argc, char **argv)
{
    if(rs::setup() == 0)
    {
        rs::Motor motor {"Motor Left"};
        motor.define(14, 18, 15);
        motor.write(rs::FORWARD);

        rs::Gpio led {21};
        led.write(rs::ON);
    }

    rs::SockServer server {"192.168.1.52", 8998};
    if(server.bind_sock() == 0)
    {
        if(server.listen_clients(1) == 0)
        {
            int signal {0};
            signal = server.received();
            rs::out("received : $i", signal);
        }
    }

    return 0;
}