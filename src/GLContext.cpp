#include "GLContext.hpp"

#include <iostream>
#include <stdexcept>

GLContext::GLContext(const std::string & name, unsigned short width, unsigned short height)
    : window { initialiseGLFW(name, width, height) }
{
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

GLFWwindow * GLContext::initialiseGLFW(const std::string & name, unsigned short width, unsigned short height)
{
    glfwSetErrorCallback(GLContext::errorCallback);

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialise GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow * window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window with GLFW");
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

void GLContext::errorCallback(int error, const char * description)
{
    std::cerr << "GLFW Error (" << error << ") " << description << std::endl;
}
