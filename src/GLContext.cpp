#include "GLContext.hpp"

#include <iostream>

void glfwErrorCallback(int error, const char * description)
{
    std::cout << "GLFW Error (" << error << ") " << description << std::endl;
}

GLContext::GLContext(const std::string & name, unsigned short width, unsigned short height)
{
    glfwSetErrorCallback(glfwErrorCallback);

    // Initialise GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialise GLFW");
    }

    // Create window with GLFW
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(
        width,
        height,
        name.c_str(),
        nullptr,
        nullptr
    );

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window with GLFW");
    }

    // Make window the current OpenGL context
    glfwMakeContextCurrent(window);

    // Initialise GLEW
    glewExperimental = static_cast<GLboolean>(true);
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialise GLEW");
    }

    // Set GLFW Options
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

GLContext::~GLContext()
{
    glfwTerminate();
}

void GLContext::loop()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool GLContext::isActive() const
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window);
}
