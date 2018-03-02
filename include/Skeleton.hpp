#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class Skeleton {
private:
    static const std::vector<GLfloat> SKULL_VERTICES;

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
    Skeleton(const std::string & appName, unsigned int width, unsigned int height);
    ~Skeleton();

    void loop();
    bool isActive();
};

