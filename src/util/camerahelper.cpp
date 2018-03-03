#include "util/camerahelper.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 camerahelper::getNormalisedViewProjection(unsigned short width, unsigned short height)
{
    float ratio = static_cast<float>(height) / static_cast<float>(width);
    glm::mat4 projection = glm::ortho(-0.5f, 0.5f, -0.5f * ratio, 0.5f * ratio, 0.0f, 1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    return projection * view;
}
