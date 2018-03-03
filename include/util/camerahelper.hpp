#pragma once

#include <glm/glm.hpp>

namespace camerahelper
{
    glm::mat4 getNormalisedViewProjection(unsigned short width, unsigned short height);
}