#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <string>

class GLContext
{
private:
    GLFWwindow * window;

    static GLFWwindow * initialiseGLFW(const std::string &, unsigned short, unsigned short);
    static void errorCallback(int, const char *);
public:
    GLContext(const std::string & name, unsigned short width, unsigned short height);
    ~GLContext();

    void loop();
    bool isActive() const;
};
