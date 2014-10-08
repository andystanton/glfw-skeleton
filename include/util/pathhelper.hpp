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
    unique_ptr<string> getApplicationPathAndName();
    unique_ptr<string> getApplicationPath();
    unique_ptr<string> getApplicationName();
};

