#include "util/cli/CLIParser.hpp"

const regex CLIParser::cliKeyValuePattern = regex("--?([\\w\\d-]+)=([\\w\\d-]+)");
const regex CLIParser::cliSwitchPattern = regex("-?-?([\\w\\d-]+)");

Configuration & CLIParser::getConfiguration()
{
    return configuration;
}

string CLIParser::toLowerCase(string original)
{
    string value(original);
    std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    return value;
}

vector<string> CLIParser::argToVec(int argc, char ** argv)
{
    vector<string> vec;
    for (int i = 0; i < argc; ++i)
    {
        vec.push_back(argv[i]);
    }
    return vec;
}

map<string, string> CLIParser::vecToMap(vector<string> arguments)
{
    map<string, string> configMap;

    if (arguments.size() > 1)
    {
        for (auto argument : arguments)
        {
            std::smatch sm;
            if (regex_match(argument, sm, cliKeyValuePattern))
            {
                configMap[toLowerCase(sm[1])] = toLowerCase(sm[2]);
            } else if (regex_match(argument, sm, cliSwitchPattern))
            {
                configMap[toLowerCase(sm[1])] = string("true");
            }
        }
    }
    return configMap;
}

CLIParser::CLIParser(int argc, char ** argv)
        : CLIParser(argToVec(argc, argv))
{

}


CLIParser::CLIParser(vector<string> arguments)
    : configuration(vecToMap(arguments))
{

}

CLIParser::~CLIParser()
{

}