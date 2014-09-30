#include "util/log/Logger.hpp"

const string Logger::message_ok = string(" ... \033[1;32mOK\033[0m");
const string Logger::message_fail = string(" ... \033[1;31mFail\033[0m");

const regex Logger::colourPattern = regex("\\\033\\[\\d+\\;?\\d*m");

Logger::Logger(string loggerName, bool noColour)
    : loggerName(loggerName)
    , logEntry()
    , noColour(noColour)
{
}

Logger::~Logger()
{
}

Logger & Logger::operator << (const string & message)
{
    // If there's nothing in the stringstream yet, prepend with the logger name
    if (logEntry.str().empty()) {
        logEntry << "[" << loggerName << "] ";
    }

    // Output log message, stripping colours using regex replace if required.
    try
    {
        logEntry << (noColour ? regex_replace(message, colourPattern, string("")) : message);
    } catch (std::regex_error)
    {
        logEntry << message;
    }

    return *this;
}

Logger & Logger::operator << (const LoggerMode mode)
{
    switch (mode) {
        case endl:
            // Output the stringstream to standard out and reset the stringstream.
            // Be sure to use 'std::endl' as 'endl' will refer to LoggerMode::endl by default.
            cout << logEntry.str() << std::endl;


            logEntry.clear();
            logEntry.str(string(""));
            break;
        case ok:
            *this << message_ok;
            break;
        case fail:
            *this << message_fail;
            break;
        default:
            break;
    }

    return *this;
}

