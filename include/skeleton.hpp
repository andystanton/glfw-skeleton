#ifndef _SKELETON_SKELETON
#define _SKELETON_SKELETON

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util/shaderhelper.hpp"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

namespace skeleton {
    static float width;
    static float height;
    static string appName;

    static const string ok(" ... \033[1;32mOK\033[0m");
    static const string fail(" ... \033[1;31mFail\033[0m");

    static GLFWwindow * window;

    static GLuint posId;
    static GLuint colourId;
    static GLuint scaleId;
    static GLuint matrixId;
    static GLuint vertexbuffer;
    static GLuint vertexArrayId;
    static GLuint programId;

    static glm::mat4 MVP;

    static const GLfloat skullVertices[] =
    {
        // top of skull
         60, 50,
         60,  0,
        -60,  0,
        -60, 50,
         60, 50,
        -60,  0,

        // left of eyes
        -60,   0,
        -40,   0,
        -60, -30,
        -60, -30,
        -40,   0,
        -40, -30,

        // centre of eyes
        -10,   0,
         10,   0,
        -10, -30,
        -10, -30,
         10,   0,
         10, -30,

        // right of eyes
         60,   0,
         40,   0,
         60, -30,
         60, -30,
         40,   0,
         40, -30,

        // left of nose
        -60, -30,
          0, -30,
        -10, -40,
        -10, -40,
        -60, -40,
        -60, -30,

        // right of nose
          0, -30,
         60, -30,
         10, -40,
         10, -40,
         60, -30,
         60, -40,

        // jaw
        -30, -40,
         30, -40,
        -30, -55,
        -30, -55,
         30, -40,
         30, -55,
    };

    void initGL();
    void drawSkull(float x, float y);
    void setup(const string & appName, float width, float height);
    void loop();
    void teardown();
    bool isActive();
};

#endif
