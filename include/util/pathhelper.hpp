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

using std::string;
using std::unique_ptr;

namespace pathhelper {
    string getApplicationPathAndName();
    string getApplicationPath();
    string getApplicationName();
};

