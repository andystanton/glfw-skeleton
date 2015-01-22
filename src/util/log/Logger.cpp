#include "util/log/Logger.hpp"

const unsigned int Logger::DEFAULT_MAX_NAME_LENGTH = 12;

const string Logger::COLOUR_PATTERN = string("\\\033\\[(\\d+\\;)?\\d+m");
const string Logger::COLOUR_TEMPLATE = string("\033[{{intensity}};3{{colour}}m");

const map<const Logger::LoggerColour, const int> Logger::COLOUR_MAP = {
        { black     , 0 },
        { red       , 1 },
        { green     , 2 },
        { yellow    , 3 },
        { blue      , 4 },
        { magenta   , 5 },
        { cyan      , 6 },
        { white     , 7 },
};

const map<const Logger::LoggerMode, const string> Logger::MODE_MAP = {
        { bold  , "\033[1m" },
        { reset , "\033[0m" },
};

Logger::Logger(string loggerName, bool noColour)
try : loggerName(loggerName)
        , logEntry()
        , colourRegex(Logger::COLOUR_PATTERN)
        , noColour(noColour)
        , isBright(false)
{
}
catch(std::regex_error)
{
    noColour = true;
}


Logger::~Logger()
{
}

string Logger::getHeader()
{
    stringstream header;
    header << withMode(reset) << withColour(yellow) << " ";

    if (loggerName.size() > DEFAULT_MAX_NAME_LENGTH)
    {
        header << loggerName.substr(0, DEFAULT_MAX_NAME_LENGTH - 3) << string(3, '.');
    }
    else
    {
        header << string(DEFAULT_MAX_NAME_LENGTH - loggerName.size(), ' ') << loggerName;
    }

    header << withMode(reset) << " : ";

    return header.str();
}

string replaceInString(const string & original, const string searchString, const string replacement)
{
    string updated(original);
    if (original.find(searchString) != string::npos)
    {
        updated.replace(updated.find(searchString), searchString.size(), replacement);
    }
    return updated;
}

string Logger::decorateString(const string & original, const LoggerColour colour)
{
    string brightened = replaceInString(original, "{{intensity}}", isBright ? "1" : "0");
    string colourised = replaceInString(brightened, "{{colour}}", to_string(COLOUR_MAP.at(colour)));

    return colourised;
}

string Logger::filterColours(string const & original)
{
    return noColour ? regex_replace(original, colourRegex, string()) : original;
}

string Logger::withColour(const LoggerColour colour)
{
    stringstream colourString;
    if (COLOUR_MAP.find(colour) != COLOUR_MAP.end())
    {
        colourString << decorateString(COLOUR_TEMPLATE, colour);
    }
    return colourString.str();
}

string Logger::withMode(const LoggerMode mode)
{
    if (mode == Logger::bold) isBright = true;
    if (mode == Logger::reset) isBright = false;

    stringstream modeString;
    if (MODE_MAP.find(mode) != MODE_MAP.end())
    {
        modeString << filterColours(MODE_MAP.at(mode));
    }
    return modeString.str();
}

string Logger::withPreset(const LoggerPreset preset)
{
    stringstream presetString;
    switch (preset) {
        case ok:
            presetString << withMode(bold) << " ... " << withColour(green) << "OK" << withMode(reset);
            break;
        case fail:
            presetString << withMode(bold) << " ... " << withColour(red) << "Fail" << withMode(reset);
            break;
        default:
            break;
    }
    return presetString.str();
}

Logger & Logger::operator << (const string & message)
{
    logEntry << message;
    return *this;
}

Logger & Logger::operator << (const LoggerColour colour)
{
    *this << withColour(colour);
    return *this;
}

Logger & Logger::operator << (const LoggerPreset preset)
{
    *this << withPreset(preset);
    return *this;
}

Logger & Logger::operator << (const LoggerMode mode)
{
    switch (mode) {
        case endl:
            cout << filterColours(getHeader()) << filterColours(logEntry.str()) << withMode(reset) << std::endl;
            logEntry.clear();
            logEntry.str(string());
            break;
        default:
            *this << withMode(mode);
            break;
    }
    return *this;
}

