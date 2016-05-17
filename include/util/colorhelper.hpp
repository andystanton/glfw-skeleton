#pragma once

#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

using std::string;

namespace colorhelper {
    glm::vec4 rgbaDecToVec4(float r, float g, float b, float a);
    glm::vec4 rgbDecToVec4(float r, float g, float b);

    glm::vec4 rgbaHexToVec4(const string & rgb, float a);
    glm::vec4 rgbHexToVec4(const string & rgb);

    int hexPairToInt(char first, char second);
};
