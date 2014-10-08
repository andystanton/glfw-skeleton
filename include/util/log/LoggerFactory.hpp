#pragma once

#include <memory>
#include <map>

#include "Logger.hpp"

using std::shared_ptr;
using std::map;

class LoggerFactory
{
public:
    static shared_ptr<Logger> getLogger(string loggerName);
    static void configure(bool noColour);
private:
    LoggerFactory() {};
    ~LoggerFactory() {};
    static map<string, shared_ptr<Logger>> loggers;
    static bool noColour;
};
