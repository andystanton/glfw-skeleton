#include "util/cli/CLIParser.hpp"

const string CLIParser::CLI_KEY_VALUE_PATTERN = string("--?([\\w\\d-]+)=([\\w\\d-]+)");
const string CLIParser::CLI_SWITCH_PATTERN = string("-?-?([\\w\\d-]+)");

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
        try
        {
            for (auto argument : arguments)
            {
                std::smatch sm;
                if (regex_match(argument, sm, regex(CLI_KEY_VALUE_PATTERN)))
                {
                    configMap[toLowerCase(sm[1])] = toLowerCase(sm[2]);
                } else if (regex_match(argument, sm, regex(CLI_SWITCH_PATTERN)))
                {
                    configMap[toLowerCase(sm[1])] = string("true");
                }
            }
        } catch (const std::regex_error & error)
        {
            std::cerr << "Regex error - unable to parse command line arguments" << std::endl;
            std::cerr << error.code() << ": " << error.what() << std::endl;
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