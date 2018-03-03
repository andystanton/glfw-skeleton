#pragma once

#include "GLContext.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>

class Skeleton {
private:
    static const std::vector<GLfloat> SKULL_VERTICES;

    GLContext context;
    GLuint programId;
    GLuint vao;
    GLuint vbo;
    GLint uniform_viewProjection;
    GLint uniform_color;
    glm::mat4 viewProjection;
    glm::vec4 foregroundColor;
    glm::vec4 backgroundColor;

    void drawSkull(glm::vec4 color);

public:
    Skeleton(const std::string & appName, unsigned short width, unsigned short height);
    ~Skeleton();

    void loop();
    bool isActive();
};

