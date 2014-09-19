#pragma once

#include "Configuration.hpp"

#include <string>
#include <regex>
#include <sstream>
#include <vector>

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
    static const regex cliKeyValuePattern;
    static const regex cliSwitchPattern;
    vector<string> argToVec(int argc, char ** argv);
    map<string, string> vecToMap(vector<string>);
    string toLowerCase(string key);
};