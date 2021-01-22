# raslib : C++ oriented-object library for Raspberry Pi
This library include a management module for **GPIO** pins and a management module based on first module for motors with L298N controller.\
The main objective of this library is to enable people to use **easily** their Raspberry and create **quickly** many projects.\
I wanted to use **C++** with my new Raspberry Pi and I don't found **object-oriented** library in **C++** for that. I've made enquiries to create my own library, it finnaly came out. I added tiny options to facilitate the life of programmer !\
I'm new to in the world of **C/C++**, you can suggest changes to me, ther is'nt problems ! I prefer to you suggest me and report inconsistencies to me, rather than my library remaining bad. The aim is to progress.\
\
***About copyright*** : *my library is opensource and you can use it like you want but I like to be mentioned. Don't steal their but make changes and re-publish them again. Otherwise it's useless.*
#
## Add raslib library in your project :
**Download** the .zip file [here](https://github.com/antoninhrlt/antoninhrlt.github.io/archive/main.zip)\
**Unzip** the .zip file\
**Copy** "lib/raslib" folder vers the "include" folder of your projet folders\
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
    Gpio led {"Led"};

    if(!led.setup())
    {
        led.set_pin(21);
        led.output(ON);
    }

    return 0;
}
```
#
## Control a motor with L298N controller and raslib
Connections look like this: ![](https://alcalyn.github.io/assets/images/rpi-motors/rasp-l298n.png) 
*from https://alcalyn.github.io/ *\
"src/main.cpp" :
```cpp
#include "raslib/raslib.hpp"
#include "raslib/motor.hpp"

int main(int argc, char* argv[])
{
    Motor motor {"Motor"};
    if(!motor.setup())
        motor.set_pins(14, 18, 15);

    Motor motor2 {"Motor2"};
    if(!motor2.setup())
        motor2.set_pins(25, 8, 7);

    while(true)
    {
        sleep(5000);
        // forward
        motor.output(ON);
        motor2.output(ON);

        sleep(5000);
        // stop
        motor.output(OFF); 
        motor2.output(OFF);
    }

    return 0;
}
```
