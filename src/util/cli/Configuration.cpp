#include "util/cli/Configuration.hpp"

Configuration::Configuration(map<string, string> configMap)
    : configMap(configMap)
{

}

Configuration::~Configuration()
{

}

bool Configuration::containsKey(string key)
{
    return configMap.find(key) != configMap.end();
}

string Configuration::getValue(string key)
{
    return configMap[key];
}

bool Configuration::getBoolValue(string key)
{
    string value(configMap[key]);
    bool boolValue = false;
    std::istringstream(value) >> std::boolalpha >> boolValue;
    return boolValue;
}

int Configuration::getIntValue(string key)
{
    return stoi(configMap[key]);
}
