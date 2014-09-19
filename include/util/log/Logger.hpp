#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <regex>

using std::string;
using std::regex;
using std::stringstream;
using std::cout;

class LoggerFactory;

class Logger
{
friend class LoggerFactory;
public:
    enum LoggerMode
    {
        ok,
        fail,
        endl
    };

    Logger & operator<< (const string & message);
    Logger & operator<< (const LoggerMode);

    ~Logger();
private:
    Logger(string loggerName, bool noColour);

    string loggerName;
    stringstream logEntry;
    bool noColour;

    static const regex colourPattern;
    static const string message_ok;
    static const string message_fail;
};

