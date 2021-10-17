#include "util/pathhelper.hpp"

#include <climits>
#include <stdexcept>
#if defined (__APPLE__)
#include <libproc.h>
#include <unistd.h>
#elif defined(__linux__)
#include <unistd.h>
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <Windows.h>
#include <string>
#include <iostream>
#include <Shlobj.h>
#include <locale>
#include <codecvt>
#endif

std::string pathhelper::getApplicationPathAndName()
{
    std::string fullPath;
#if defined (__APPLE__)
    char pathBuffer[PROC_PIDPATHINFO_MAXSIZE];
    pid_t pid = getpid();
    int ret = proc_pidpath(pid, pathBuffer, sizeof(pathBuffer));
    if (ret <= 0) {
        throw std::runtime_error("Unable to ascertain application path");
    } else {
        fullPath = pathBuffer;
    }
#elif defined(__linux__)
    char pathBuffer[1024];
    ssize_t len = readlink("/proc/self/exe", pathBuffer, sizeof(pathBuffer)-1);
    if (len != -1) {
        pathBuffer[len] = '\0';
        fullPath = pathBuffer;
    } else {
        throw std::runtime_error("Unable to ascertain application path");
    }
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	wchar_t buffer[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	auto exePath = std::wstring(buffer).substr(0, pos);
	fullPath = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(exePath);
#else
    throw std::runtime_error("OS not supported for finding paths");
#endif

    return fullPath;
}

std::string pathhelper::getApplicationPath()
{
    std::string fullPath = getApplicationPathAndName();
    return fullPath.substr(0, fullPath.find_last_of('/'));
}
