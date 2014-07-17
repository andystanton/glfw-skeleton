#ifndef _SKELETON_PATH_HELPER
#define _SKELETON_PATH_HELPER

#include <string>
#include <unistd.h>
#include <limits.h>

using std::unique_ptr;

#if defined (__APPLE__)
    #include <libproc.h>
#endif

using std::string;

namespace pathhelper {
    unique_ptr<string> getApplicationPathAndName();
    unique_ptr<string> getApplicationPath();
    unique_ptr<string> getApplicationName();
};

#endif
