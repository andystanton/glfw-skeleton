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
    regex colourRegex;
    bool noColour;

    static const string COLOUR_PATTERN;
    static const string MESSAGE_OK;
    static const string MESSAGE_FAIL;
};

