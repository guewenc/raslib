#if !defined(__RASLIB__)
#define __RASLIB__

#include <string>
#include <fstream>
#include <unistd.h>

namespace raslib
{
    bool const ON {1};
    bool const OFF {0};

    bool const LOGS {true}; // 0
    bool const NO_LOGS {false}; // 1

    bool const FORWARD {1};
    int const BACKWARD {2};
    bool const STOP {0};



    int setup(bool const);
    void sleep(int const);
}

#endif