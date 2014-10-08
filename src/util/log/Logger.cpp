#include "util/log/Logger.hpp"

const string Logger::MESSAGE_OK = string(" ... \033[1;32mOK\033[0m");
const string Logger::MESSAGE_FAIL = string(" ... \033[1;31mFail\033[0m");
const string Logger::COLOUR_PATTERN = string("\\\033\\[\\d+\\;?\\d*m");

Logger::Logger(string loggerName, bool noColour)
try : loggerName(loggerName)
    , logEntry()
    , colourRegex(Logger::COLOUR_PATTERN)
    , noColour(noColour)
{
}
catch(std::regex_error)
{
    noColour = true;
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
    logEntry << (noColour ? regex_replace(message, colourRegex, string("")) : message);

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
            *this << MESSAGE_OK;
            break;
        case fail:
            *this << MESSAGE_FAIL;
            break;
        default:
            break;
    }

    return *this;
}

