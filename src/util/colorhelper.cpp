#include "util/colorhelper.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

glm::vec4 colorhelper::rgbDecToVec4(float r, float g, float b)
{
    return rgbaDecToVec4(r, g, b, 1.0f);
}

glm::vec4 colorhelper::rgbaDecToVec4(float r, float g, float b, float a)
{
    return glm::vec4 { r, g, b, a };
}

glm::vec4 colorhelper::rgbHexToVec4(const string & rgb)
{
    return rgbaHexToVec4(rgb, 1.0f);
}

glm::vec4 colorhelper::rgbaHexToVec4(const string & rgb, float a)
{
    assert(rgb.size() == 6);
    glm::vec4 outputColour;

    const char * hexCharacters = rgb.c_str();
    for (int i = 0; i < 6; i += 2)
    {
        outputColour[i / 2] = hexPairToInt(hexCharacters[i], hexCharacters[i + 1]) / 255.f;
    }
    outputColour[3] = a;

    return outputColour;
}

int colorhelper::hexPairToInt(char first, char second)
{
    int component;
    std::stringstream stream;
    stream << first << second;
    stream >> std::hex >> component;
    return component;
}
