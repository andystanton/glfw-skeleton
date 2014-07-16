#include "util/pathhelper.hpp"

const string& getApplicationPathAndName()
{
    string fullPath;

    #if defined (__APPLE__)
        int ret;
        pid_t pid;
        char pathbuf[PROC_PIDPATHINFO_MAXSIZE];

        pid = getpid();
        ret = proc_pidpath(pid, pathbuf, sizeof(pathbuf));
        if ( ret <= 0 ) {
            throw "Unable to ascertain application path";
        } else {
            fullPath = string(pathbuf);
        }
    #elif defined(__linux__)
        char buff[1024];
        ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
        if (len != -1) {
            buff[len] = '\0';
            fullPath = string(buff);
        } else {
            throw "Unable to ascertain application path";
        }
    #else
        throw "OS not supported for finding paths"
    #endif

    return fullPath;
}

const string& getApplicationPath()
{
    const string& fullPath = getFullApplicationPath();
    return fullPath.substr(0, fullPath.find_last_of("/"));
}

const string& getApplicationName()
{
    const string& fullPath = getFullApplicationPath();
    return fullPath.substr(fullPath.find_last_of("/") + 1, fullPath.length());
}
