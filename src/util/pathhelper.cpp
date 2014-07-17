#include "util/pathhelper.hpp"

unique_ptr<string> pathhelper::getApplicationPathAndName()
{
    string * fullPath;
    #if defined (__APPLE__)
        int ret;
        pid_t pid;
        char pathbuf[PROC_PIDPATHINFO_MAXSIZE];

        pid = getpid();
        ret = proc_pidpath(pid, pathbuf, sizeof(pathbuf));
        if ( ret <= 0 ) {
            throw "Unable to ascertain application path";
        } else {
            fullPath = new string(pathbuf);
        }
    #elif defined(__linux__)
        char buff[1024];
        ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
        if (len != -1) {
            buff[len] = '\0';
            fullPath = new string(buff);
        } else {
            throw "Unable to ascertain application path";
        }
    #else
        throw "OS not supported for finding paths"
    #endif

    return unique_ptr<string>(fullPath);
}

unique_ptr<string> pathhelper::getApplicationPath()
{
    unique_ptr<string> fullPath = getApplicationPathAndName();
    string * applicationPath = new string(fullPath->substr(0, fullPath->find_last_of("/")));
    return unique_ptr<string>(applicationPath);
}

unique_ptr<string> pathhelper::getApplicationName()
{
    unique_ptr<string> fullPath = getApplicationPathAndName();
    string * applicationName = new string(fullPath->substr(fullPath->find_last_of("/") + 1, fullPath->length()));
    return unique_ptr<string>(applicationName);
}
