#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <map>

using std::string;
using std::regex;
using std::stringstream;
using std::cout;
using std::map;
using std::to_string;

class LoggerFactory;

class Logger
{
    friend class LoggerFactory;
public:
    enum LoggerColour   { black, red, green, yellow, blue, magenta, cyan, white };
    enum LoggerPreset   { ok, fail };
    enum LoggerMode     { bold, reset, endl };

    Logger & operator<< (const string & message);
    Logger & operator<< (const LoggerColour);
    Logger & operator<< (const LoggerPreset);
    Logger & operator<< (const LoggerMode);

    ~Logger();
private:
    Logger(string loggerName, bool noColour);

    string loggerName;
    stringstream logEntry;
    regex colourRegex;
    bool noColour;
    bool isBright;

    string decorateString(const string &, const LoggerColour);
    string filterColours(const string &);

    string withColour(const LoggerColour);
    string withMode(const LoggerMode);
    string withPreset(const LoggerPreset);

    string getHeader();

    static const unsigned int DEFAULT_MAX_NAME_LENGTH;
    static const string COLOUR_PATTERN;
    static const string COLOUR_TEMPLATE;
    static const map<const LoggerColour, const int> COLOUR_MAP;
    static const map<const LoggerMode, const string> MODE_MAP;
};

