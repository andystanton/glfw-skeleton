#include "Skeleton.hpp"

#include "util/colorhelper.hpp"
#include "util/shaderhelper.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

Skeleton::Skeleton(const std::string & appName, unsigned int width, unsigned int height)
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * SKULL_VERTICES.size(), SKULL_VERTICES.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
    // Use shader and set uniforms
    glUseProgram(programId);

    glUniformMatrix4fv(uniform_viewProjection, 1, GL_FALSE, glm::value_ptr(viewProjection));
    glUniform2fv(uniform_offset, 1, glm::value_ptr(offset));
    glUniform4fv(uniform_color, 1, glm::value_ptr(color));
    glUniform1f(uniform_scale, scale);

    // Bind the Vertex Array Object and draw the contents of its bound vertex buffer as triangles
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(SKULL_VERTICES.size()));

    // Unbind VAO and shader
    glBindVertexArray(0);
    glUseProgram(0);
}

void Skeleton::loop()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSkull(glm::vec2(width / 2.f, height / 2.f), 1.6f, foregroundColor);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Skeleton::isActive()
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window);
}

const std::vector<GLfloat> Skeleton::SKULL_VERTICES {
    // top of skull
    60.f, 50.f,
    60.f, 0.f,
    -60.f, 0.f,
    -60.f, 50.f,
    60.f, 50.f,
    -60.f, 0.f,

    // left of eyes
    -60.f, 0.f,
    -40.f, 0.f,
    -60.f, -30.f,
    -60.f, -30.f,
    -40.f, 0.f,
    -40.f, -30.f,

    // centre of eyes
    -10.f, 0.f,
    10.f, 0.f,
    -10.f, -30.f,
    -10.f, -30.f,
    10.f, 0.f,
    10.f, -30.f,

    // right of eyes
    60.f, 0.f,
    40.f, 0.f,
    60.f, -30.f,
    60.f, -30.f,
    40.f, 0.f,
    40.f, -30.f,

    // left of nose
    -60.f, -30.f,
    0.f, -30.f,
    -10.f, -40.f,
    -10.f, -40.f,
    -60.f, -40.f,
    -60.f, -30.f,

    // right of nose
    0.f, -30.f,
    60.f, -30.f,
    10.f, -40.f,
    10.f, -40.f,
    60.f, -30.f,
    60.f, -40.f,

    // jaw
    -30.f, -40.f,
    30.f, -40.f,
    -30.f, -55,
    -30.f, -55,
    30.f, -40.f,
    30.f, -55.f,
};
