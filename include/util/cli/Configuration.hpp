#pragma once

#include <map>
#include <string>
#include <sstream>

using std::map;
using std::string;

class Configuration
{
public:
    Configuration(map<string, string>);
    ~Configuration();

    bool containsKey(string key);
    string getValue(string key);
    int getIntValue(string key);
    bool getBoolValue(string key);
private:
    map<string, string> configMap;
};