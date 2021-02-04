# raslib : C++ oriented-object library for Raspberry Pi
This library include a management module for **GPIO** pins and a management module based on first module for motors with L298N controller.\
The main objective of this library is to enable people to use **easily** their Raspberry and create **quickly** many projects.\
I wanted to use **C++** with my new Raspberry Pi and I don't found **object-oriented** library in **C++** for that. I've made enquiries to create my own library, it finnaly came out. I added tiny options to facilitate the life of programmer !\
I'm new to in the world of **C/C++**, you can suggest changes to me, ther is'nt problems ! I prefer to you suggest me and report inconsistencies to me, rather than my library remaining bad. The aim is to progress.\
\
***About copyright*** : *my library is opensource and you can use it like you want but I like to be mentioned. Don't steal their but make changes and re-publish them again. Otherwise it's useless.*
#
## Add raslib library in your project :
**Download** the .zip file [here](https://github.com/antoninhrlt/raslib/archive/main.zip)\
**Unzip** the .zip file\
**Copy** "lib/raslib" folder to the "include" folder of your projet folders\
Normally, it should look like this :
```
> /home/$USER/Documents/my_project
> C:/Users/%user%/Documents/my_project

    - bin
    - include
        - raslib
            * files...
    - res
    - src
        * main.cpp
```
#
## Write your first program with raslib
Simple blink on GPIO21 (The pin at the bottom left on Raspberry Pi 4B)\
"src/main.cpp" :
```cpp
#include "raslib/raslib.hpp"
#include "raslib/gpio.hpp"

int main(int argc, char* argv[])
{
    rl::Gpio led {"Led"};

    if(!rl::setup(true /* --> LOGS */))
    {
        led.set_pin(21);
        while(true)
        {
            led.output(rl::ON);
            rl::sleep(500);
            led.output(rl::OFF);
            rl::sleep(500);
        }
    }
    else
    {
        return rl::log("Setup failed", -1);
    }

    return 0;
}
```
**Compile** : `g++ src/main.cpp -o bin/prog -I include`
#
# Or just turn on a led
"src/main.cpp" :
```cpp
#include "raslib/raslib.hpp"
#include "raslib/gpio.hpp"

int main(int argc, char* argv[])
{
    rl::Gpio led {"Led"};

    if(!rl::setup(true /* --> LOGS */))
    {
        led.set_pin(21);
        led.output(rl::ON);
    }
    else
    {
        return rl::log("Setup failed", -1);
    }

    return 0;
}
```
#
## Control a motor with L298N controller and raslib
Connections look like this: ![](https://alcalyn.github.io/assets/images/rpi-motors/rasp-l298n.png) 
*from [https://alcalyn.github.io](https://alcalyn.github.io/)*\
"src/main.cpp" :
```cpp
#include "raslib/raslib.hpp"
#include "raslib/motor.hpp"

int main(int argc, char* argv[])
{
    if(!rl::setup(true /* --> LOGS */))
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
```
