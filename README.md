# raslib : C++ oriented-object library for Raspberry Pi

This library include a management module for **GPIO** pins and a management module based on first module for motors with L298N controller.\
The main objective of this library is to enable people to use **easily** their Raspberry and create **quickly** many projects.
I wanted to use **C++** with my new Raspberry Pi and I don't found **object-oriented** library in **C++** for that. I've made enquiries to create my own library, it finnaly came out. I added tiny options to facilitate the life of programmer !
I'm new to in the world of **C/C++**, you can suggest changes to me, ther is'nt problems ! I prefer to you suggest me and report inconsistencies to me, rather than my library remaining bad. The aim is to progress.

***About copyright*** : *my library is opensource and you can use it like you want but I like to be mentioned. Don't steal their but make changes and re-publish them again. Otherwise it's useless.*

# Release Notes *(Version : 1.2)* :

The library has been totally revisited in its version 1.2, but if the version has not become 2.x it's because the changes are not really at the code level, indeed the changes that have been made are :

- The separation of header files (.cpp and .hpp)
- Changing namespace to "raslib" instead of "rl" who was considered too implicit.
- The removing the logs (in fact, when calling the "raslib::setup()" function, for the moment, whether you choose "raslib::NO_LOGS" or "raslib::LOGS" it has no impact, the logs are disabled but will come back in version 1.3. Some changes have to be made and this can't be done immediately.
  So it's not really a new version of raslib full of new features but a revisit of version 1.1 (which is not publicly available anymore).

## Add raslib library in your project :

**Download** the .zip file [here](https://github.com/antoninhrlt/raslib/archive/main.zip)
**Unzip** the .zip file
**Copy** "include/raslib" folder to the "include" folder of your project folder
Normally, it should look like this :

```
> /home/$USER/my_project
    - bin
    - include
        - raslib
            * files...
    - res
    - src
        * main.cpp
```

## Write your first program with raslib

Turn on a led on GPIO 21 (The pin at the bottom left on Raspberry Pi 4B)
"src/main.cpp" :

```cpp
#include "raslib/raslib.hpp"
#include "raslib/rasgpio.hpp"

int main(int argc, char* argv[])
{
    raslib::gpio blue_led {"Blue led"};

    if(!raslib::setup(raslib::NO_LOGS)) // don't show logs
    {
        blue_led.set_pin(21); // set on gpio 21
        blue_led.output(raslib::ON);
    }
    else { return -1; } // setup failed

    return 0;
}
```

**Compile** : `bash compile.sh /home/$USER/your_folder` or `cd /home/$USER/your_folder; g++ src/main.cpp include/raslib/*.cpp -o bin/prog.com -I include -std=c++17` (Note : The bash script file doesn't just execute this command, it tells you a little bit more about what happens during compilation, it will also tell you the return value and finally : the command is just faster to write.)

# Or make a blink loop

Blink a led on GPIO 21. "src/main.cpp" :

```cpp
#include "raslib/raslib.hpp"
#include "raslib/rasgpio.hpp"

int main(int argc, char* argv[])
{
    raslib::gpio blue_led {"Blue led"};

    if(!raslib::setup(raslib::NO_LOGS)) // don't show logs
    {
        blue_led.set_pin(21); // set on gpio 21
        while(true)
        {
            blue_led.output(raslib::ON);
            raslib::sleep(500); // 500ms
            blue_led.output(raslib::OFF);
            raslib::sleep(500);
        }
    }
    else { return -1; } // setup failed

    return 0;
}
```

## Control a motor with L298N controller and raslib

Connections look like this: ![](https://alcalyn.github.io/assets/images/rpi-motors/rasp-l298n.png) 
*from [https://alcalyn.github.io](https://alcalyn.github.io/)*\
A loop that moves the wheels forward every 5 seconds. "src/main.cpp" :

```cpp
#include "raslib/raslib.hpp"
#include "raslib/rasmotor.hpp"

int main(int argc, char* argv[])
{
    if(!raslib::setup(raslib::NO_LOGS)) // don't show logs
    {
        raslib::motor motor_1 {"Motor 1"};
        raslib::motor motor_2 {"Motor 2"};

        motor_1.set_pins(14, 18, 15);
        motor_2.set_pins(25, 8, 7);
        
        while(true)
        {
            // forward
            motor_1.output(raslib::FORWARD);
            motor_2.output(raslib::FORWARD);
            raslib::sleep(5000);

            // stop
            motor_1.output(raslib::STOP); 
            motor_2.output(raslib::STOP);
            raslib::sleep(5000);
        }
    }
    else { return -1; } // setup failed

    return 0;
}
```
