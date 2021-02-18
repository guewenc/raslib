# raslib
## raslib is an Raspberry PI library written in C++ OO

A day, I wanted to use C++ with my Raspberry PI 4B, and I don't have find any library who is written in C++ oriented-object that I liked. Like say the proverb : "be the change you want to see" (Gandhi). So I wrote this library. Enjoy ! [Website](https://antoninhrlt.github.io/raslib)

### Elements of the library :
 - GPIO controller
 - Motor controller (Written thanks to the GPIO controller, it's only a class allowing to reduce the working time. Make for L298N controller)
 - Socket generator (Only the server.. to you to create the client on an Android app for example. Find [here](https://github.com/antoninhrlt/rasdroid) my Android application to remotely control my Raspberry PI robot)
 - Script to compile easily your project (Coming soon : the possibility to make "configuration file" for the script. In the meantime, all you have to do is edit the python file)

---

## Your first script
Blink a led with infinite loop
```cpp
#include <raslib/gpio/gpio.hpp>

int main(int argc, char **argv)
{
    if(rs::setup() == 0)
    {
        rs::Gpio led {21}; 
        // or "led.define(21)" to set the pin with empty constructor
        while(true)
        {
            led.write(rs::ON);
            rs::sleep(500);
            led.write(rs::OFF);
            rs::sleep(500);
        }
    }

    return 0;
}
```
Assuming your project folder look like this :
```
- bin
- include
    - raslib
        - gpio
        - motor
        - socket
- src
    main.cpp

compile.py
```

 **Compile : ```$ python3 compile.py```**

---

## Control a motor with L298N controller

Engines that moves forward and stops every 5 seconds
```cpp
#include <raslib/motor/motor.hpp>

int main(int argc, char **argv)
{
    if(rs::setup() == 0)
    {
        rs::Motor motor2 {"Motor 1", 25, 8, 7};
        rs::Motor motor1 {"Motor 2"};
        motor1.define(14, 18, 15);
        
        while(true)
        {
            motor1.write(rs::FORWARD);
            motor2.write(rs::FORWARD);
            rs::sleep(5000);
            
            motor1.write(rs::STOP);
            motor2.write(rs::STOP);
            rs::sleep(5000);
        }
    }

    return 0;
}
```
Your connections :
*from https://alcalyn.github.io/assets/images/rpi-motors/rasp-l298n.png*
![Scheme](https://alcalyn.github.io/assets/images/rpi-motors/rasp-l298n.png)

---

## Listen for 1 client on local wifi
```cpp
#include <raslib/socket/socket.hpp>

int main(int argc, char **argv)
{
    // IP of Raspberry PI (find yours with "hostname -I" command)
    std::string const ip {"192.168.1.52"};

    rs::SockServer server {ip, 8998 /* Port you want */};
    if(server.bind_sock() == 0)
    {
        if(server.listen_clients(1) == 0)
        {
            int signal {0};
            signal = server.received(); // waiting to receive signal
            rs::out("Received : $i", signal);
        }
    }

    return 0;
}
```

---

If you have a bug, please let me informed : send [mail](mailto:antonherault@gmail.com) with "raslib: + name of your error" at subject.