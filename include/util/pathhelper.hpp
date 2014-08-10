#ifndef _SKELETON_PATH_HELPER
#define _SKELETON_PATH_HELPER

#include <string>
#include <climits>

using std::unique_ptr;

#if defined (__APPLE__)
    #include <libproc.h>
    #include <unistd.h>
#endif

using std::string;

namespace pathhelper {
    unique_ptr<string> getApplicationPathAndName();
    unique_ptr<string> getApplicationPath();
    unique_ptr<string> getApplicationName();
};

#endif
