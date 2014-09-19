#include "util/log/LoggerFactory.hpp"

bool LoggerFactory::noColour = false;
map<string, shared_ptr<Logger>> LoggerFactory::loggers = map<string, shared_ptr<Logger>>();

void LoggerFactory::configure(bool noColour)
{
    LoggerFactory::noColour = noColour;
}

shared_ptr<Logger> LoggerFactory::getLogger(string loggerName)
{
    if (loggers.find(loggerName) == loggers.end()) {
        loggers[loggerName] = shared_ptr<Logger>(new Logger(loggerName, LoggerFactory::noColour));
    }
    return loggers.at(loggerName);
}

