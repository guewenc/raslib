#include <raslib/gpio/gpio.hpp>
#include <raslib/motor/motor.hpp>
#include <raslib/socket/socket.hpp>
#include <thread>

void server()
{
    rs::SockServer server {"192.168.1.52", 8998};
    if(server.bind_sock() == 0)
    {
        if(server.listen_client() == 0)
        {
            while(true)
            {
                server.accept_client();
                int signal {-1};
                while(signal != 0) 
                {
                    signal = server.received();
                    rs::out("Received : $i", signal);
                }
                server.close_client();
            }
        }
    }
}

void blink()
{
    if(rs::setup() == 0)
    {
        rs::Gpio led {21};
        while(true)
        {
            led.write(rs::ON);
            rs::sleep(500);
            led.write(rs::OFF);
            rs::sleep(500);
        }
    }
}

int main(int argc, char **argv)
{
    std::thread t_server {server};
    std::thread t_blink {blink};
    t_server.join();
    t_blink.join();

    return 0;
}