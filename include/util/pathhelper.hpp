#ifndef _SKELETON_PATH_HELPER
#define _SKELETON_PATH_HELPER

#include <string>
#include <unistd.h>
#include <limits.h>

#if defined (__APPLE__)
    #include <libproc.h>
#endif

using std::string;

const string& getApplicationPathAndName();
const string& getApplicationPath();
const string& getApplicationName();

#endif
