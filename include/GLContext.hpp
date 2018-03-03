#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class GLContext
{
private:
    GLFWwindow * window;

    static GLFWwindow * initialiseGLFW(const std::string &, unsigned short, unsigned short);
public:
    GLContext(const std::string & name, unsigned short width, unsigned short height);
    ~GLContext();

    void loop();
    bool isActive() const;
};