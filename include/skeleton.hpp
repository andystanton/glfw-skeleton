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

class Skeleton {
private:
    static constexpr int SKULL_COMPONENT_COUNT = 7 * 2 * 3 * 2;

    float width;
    float height;
    string appName;

    GLFWwindow * window;

    GLuint posId;
    GLuint colourId;
    GLuint scaleId;
    GLuint matrixId;
    GLuint vertexbuffer;
    GLuint vertexArrayId;
    GLuint programId;

    glm::mat4 MVP;

    const string ok = string(" ... \033[1;32mOK\033[0m");
    const string fail = string(" ... \033[1;31mFail\033[0m");

    void initGL();
    void drawSkull(float x, float y);

public:
    Skeleton(const string & appName, float width, float height);
    ~Skeleton();

    void setup();
    void loop();
    void teardown();
    bool isActive();

    static const GLfloat skullVertices[SKULL_COMPONENT_COUNT];
};

#endif
