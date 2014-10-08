#pragma once

#include "Configuration.hpp"

#include <string>
#include <regex>
#include <sstream>
#include <vector>
#include <iostream>

using std::regex;
using std::vector;
using std::string;

class CLIParser
{
public:
    CLIParser(int argc, char ** argv);
    CLIParser(vector<string>);
    ~CLIParser();

    Configuration & getConfiguration();
private:
    Configuration configuration;

    static const string CLI_KEY_VALUE_PATTERN;
    static const string CLI_SWITCH_PATTERN;

    regex cliKeyValueRegex;
    regex cliSwitchRegex;

    vector<string> argToVec(int argc, char ** argv);
    map<string, string> vecToMap(vector<string>);
    string toLowerCase(string key);
};