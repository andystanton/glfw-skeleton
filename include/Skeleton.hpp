#pragma once

#include "GLContext.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>

class Skeleton
{
private:
    GLContext context;
    GLuint programId;
    GLuint vao;
    GLuint vbo;
    GLint uniform_color;
    glm::vec4 foregroundColor;
    glm::vec4 backgroundColor;

    static constexpr unsigned int VERTICES_COUNT = 84;
    static const GLfloat VERTICES[VERTICES_COUNT];
public:
    Skeleton(const std::string & appName, unsigned short width, unsigned short height);
    ~Skeleton();

    void loop();
    bool isActive() const;
};

