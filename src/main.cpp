#include <raslib/gpio/gpio.hpp>
#include <raslib/motor/motor.hpp>
#include <raslib/socket/socket.hpp>

int main(int argc, char **argv)
{
    if(rs::setup() != -1)
    {
        rs::Gpio led {21};
        led.write(rs::ON);
    }

    rs::SockServer server {"192.168.1.55", 8998};
    server.bind_sock();
    server.listen_clients(1);

    int signal;
    server.received(&signal);
    rs::out("$i", signal);

    return 0;
}