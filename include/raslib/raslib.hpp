#if !defined(__RASLIB__)
#define __RASLIB__

    #include <stdio.h>
    #include <stdarg.h>
    #include <unistd.h>
    #include <string>
    #include <fstream>

    namespace rs
    {
        int const FORWARD {1};
        int const BACKWARD {2};
        int const ON {1};
        int const OFF {0};

        int valid(std::string path);
        void sleep(int const time);
        int setup();
        std::string get_model();

        // output :
        void __putstr(std::string format);
        void __reset(bool *start);
        void out(std::string format, ...);
    }

#endif // __RASLIB__