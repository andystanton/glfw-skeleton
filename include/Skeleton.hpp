#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util/shaderhelper.hpp"
#include "util/colourhelper.hpp"
#include "util/log/LoggerFactory.hpp"

#include <iostream>
#include <memory>

using std::string;

class Skeleton {
private:
    static constexpr int SKULL_COMPONENT_COUNT = 7 * 2 * 3 * 2;
    static const GLfloat SKULL_VERTICES[SKULL_COMPONENT_COUNT];

    unsigned int width;
    unsigned int height;
    string appName;

    GLFWwindow * window;

    GLuint posId;
    GLuint colourId;
    GLuint scaleId;
    GLuint matrixId;
    GLuint vertexbuffer;
    GLuint vertexArrayId;
    GLuint programId;

    glm::mat4 mvp;

    shared_ptr<Logger> logger;

    void initGL();
    void drawSkull(glm::vec2 pos, float scale, glm::vec4 colour);

public:
    Skeleton(const string & appName, unsigned int width, unsigned int height);
    ~Skeleton();

    void setup();
    void loop();
    void teardown();
    bool isActive();
};

