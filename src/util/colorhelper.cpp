#include "util/colorhelper.hpp"

glm::vec4 colorhelper::hexToVec4(unsigned int hex)
{
    float divisor = 255.f;
    if (hex > 0xFFFFFFu) {
        return glm::vec4(
            ((hex >> sizeof(unsigned int) * 6) & 0xFFu),
            ((hex >> sizeof(unsigned int) * 4) & 0xFFu),
            ((hex >> sizeof(unsigned int) * 2) & 0xFFu),
            ((hex >> sizeof(unsigned int) * 0) & 0xFFu)
        ) / divisor;
    } else {
        return glm::vec4(
            ((hex >> sizeof(unsigned int) * 4) & 0xFFu),
            ((hex >> sizeof(unsigned int) * 2) & 0xFFu),
            ((hex >> sizeof(unsigned int) * 0) & 0xFFu),
            255.f
        ) / divisor;
    }
}
