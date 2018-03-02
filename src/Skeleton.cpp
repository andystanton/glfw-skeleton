#include "Skeleton.hpp"

#include <glm/gtc/type_ptr.hpp>

Skeleton::Skeleton(const string & appName, unsigned int width, unsigned int height)
    : width { width }
    , height { height }
    , foregroundColor { colorhelper::hexToVec4(0xA3B9FF) }
    , backgroundColor { colorhelper::hexToVec4(0x577EFF) }
{
    initialiseGL(appName);

    programId = shaderhelper::createProgram("shaders/2dcolor.vert", "shaders/2dcolor.frag");

    glm::mat4 projection = glm::ortho(
        0.f, static_cast<float>(width),
        0.f, static_cast<float>(height),
        0.0f, 1.0f
    );
    glm::mat4 view = glm::lookAt(
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    viewProjection = projection * view;

    uniform_offset = glGetUniformLocation(programId, "uniform_offset");
    uniform_scale = glGetUniformLocation(programId, "uniform_scale");
    uniform_color = glGetUniformLocation(programId, "uniform_color");
    uniform_viewProjection = glGetUniformLocation(programId, "uniform_viewProjection");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SKULL_VERTICES), SKULL_VERTICES, GL_STATIC_DRAW);
}

Skeleton::~Skeleton()
{
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(programId);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
}

void Skeleton::initialiseGL(const std::string & name)
{
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
    glewExperimental = (GLboolean) true;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialise GLEW");
    }

    // Set GLFW Options
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set OpenGL Options
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void Skeleton::drawSkull(glm::vec2 offset, float scale, glm::vec4 color)
{
    glUniformMatrix4fv(uniform_viewProjection, 1, GL_FALSE, glm::value_ptr(viewProjection));
    glUniform2fv(uniform_offset, 1, glm::value_ptr(offset));
    glUniform4fv(uniform_color, 1, glm::value_ptr(foregroundColor));
    glUniform1f(uniform_scale, scale);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));

    glDrawArrays(GL_TRIANGLES, 0, sizeof(SKULL_VERTICES) / sizeof(GLfloat));

    glDisableVertexAttribArray(0);
}

void Skeleton::loop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programId);

    drawSkull(glm::vec2(width / 2.f, height / 2.f), 1.6f, foregroundColor);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Skeleton::isActive()
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window);
}

const GLfloat Skeleton::SKULL_VERTICES[] = {
    // top of skull
    60, 50,
    60, 0,
    -60, 0,
    -60, 50,
    60, 50,
    -60, 0,

    // left of eyes
    -60, 0,
    -40, 0,
    -60, -30,
    -60, -30,
    -40, 0,
    -40, -30,

    // centre of eyes
    -10, 0,
    10, 0,
    -10, -30,
    -10, -30,
    10, 0,
    10, -30,

    // right of eyes
    60, 0,
    40, 0,
    60, -30,
    60, -30,
    40, 0,
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
