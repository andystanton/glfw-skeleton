#pragma once

#include <climits>
#include <memory>
#include <string>

#if defined (__APPLE__)
    #include <libproc.h>
    #include <unistd.h>
#elif defined(__linux__)
    #include <unistd.h>
#endif

namespace pathhelper {
    std::string getApplicationPathAndName();
    std::string getApplicationPath();
    std::string getApplicationName();
};

