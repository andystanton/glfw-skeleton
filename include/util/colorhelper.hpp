#pragma once

#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

using std::string;

namespace colorhelper {
    glm::vec4 hexToVec4(unsigned int);
};
