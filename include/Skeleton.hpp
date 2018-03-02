#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util/shaderhelper.hpp"
#include "util/colorhelper.hpp"

#include <iostream>
#include <memory>

using std::string;

class Skeleton {
private:
    static constexpr int SKULL_COMPONENT_COUNT = 7 * 2 * 3 * 2;
    static const GLfloat SKULL_VERTICES[SKULL_COMPONENT_COUNT];

    unsigned int width;
    unsigned int height;
    glm::vec4 foregroundColor;
    glm::vec4 backgroundColor;

    GLFWwindow * window;

    GLint uniform_viewProjection;
    GLint uniform_offset;
    GLint uniform_color;
    GLint uniform_scale;

    GLuint vbo;
    GLuint vao;
    GLuint programId;

    glm::mat4 viewProjection;

    void initialiseGL(const std::string &);
    void drawSkull(glm::vec2 pos, float scale, glm::vec4 color);

public:
    Skeleton(const string & appName, unsigned int width, unsigned int height);
    ~Skeleton();

    void loop();
    bool isActive();
};

