#include "Skeleton.hpp"

#include "util/colorhelper.hpp"
#include "util/shaderhelper.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Skeleton::Skeleton(const std::string & name, unsigned short width, unsigned short height)
    : context { name, width, height }
    , viewProjection { getNormalisedViewProjection(width, height) }
    , foregroundColor { colorhelper::hexToVec4(0xA3B9FF) }
    , backgroundColor { colorhelper::hexToVec4(0x577EFF) }
    , programId { shaderhelper::createProgram("shaders/2dcolor.vert", "shaders/2dcolor.frag") }
    , uniform_color { glGetUniformLocation(programId, "uniform_color") }
    , uniform_viewProjection { glGetUniformLocation(programId, "uniform_viewProjection") }
{
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * SKULL_VERTICES.size(), SKULL_VERTICES.data(), GL_STATIC_DRAW);

    auto attribute_pos = static_cast<GLuint>(glGetAttribLocation(programId, "attribute_pos"));
    glEnableVertexAttribArray(attribute_pos);
    glVertexAttribPointer(attribute_pos, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Skeleton::~Skeleton()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(programId);
}

void Skeleton::drawSkull(glm::vec4 color)
{
    glUseProgram(programId);

    glUniformMatrix4fv(uniform_viewProjection, 1, GL_FALSE, glm::value_ptr(viewProjection));
    glUniform4fv(uniform_color, 1, glm::value_ptr(color));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(SKULL_VERTICES.size()));

    glBindVertexArray(0);
    glUseProgram(0);
}

void Skeleton::loop()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSkull(foregroundColor);

    context.loop();
}

bool Skeleton::isActive()
{
    return context.isActive();
}

glm::mat4 Skeleton::getNormalisedViewProjection(unsigned short width, unsigned short height)
{
    float ratio = static_cast<float>(height) / static_cast<float>(width);
    glm::mat4 projection = glm::ortho(-0.5f, 0.5f, ratio / -2.f, ratio / 2.f, 0.0f, 1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    return projection * view;
}

const std::vector<GLfloat> Skeleton::SKULL_VERTICES {
    // top of skull
    0.2f, 0.166667f,
    0.2f, 0.f,
    -0.2f, 0.f,
    -0.2f, 0.166667f,
    0.2f, 0.166667f,
    -0.2f, 0.f,

    // left of eyes
    -0.2f, 0.f,
    -0.133333f, 0.f,
    -0.2f, -0.1f,
    -0.2f, -0.1f,
    -0.133333f, 0.f,
    -0.133333f, -0.1f,

    // centre of eyes
    -0.0333333f, 0.f,
    0.0333333f, 0.f,
    -0.0333333f, -0.1f,
    -0.0333333f, -0.1f,
    0.0333333f, 0.f,
    0.0333333f, -0.1f,

    // right of eyes
    0.2f, 0.f,
    0.133333f, 0.f,
    0.2f, -0.1f,
    0.2f, -0.1f,
    0.133333f, 0.f,
    0.133333f, -0.1f,

    // left of nose
    -0.2f, -0.1f,
    0.f, -0.1f,
    -0.0333333f, -0.133333f,
    -0.0333333f, -0.133333f,
    -0.2f, -0.133333f,
    -0.2f, -0.1f,

    // right of nose
    0.f, -0.1f,
    0.2f, -0.1f,
    0.0333333f, -0.133333f,
    0.0333333f, -0.133333f,
    0.2f, -0.1f,
    0.2f, -0.133333f,

    // jaw
    -0.1f, -0.133333f,
    0.1f, -0.133333f,
    -0.1f, -0.183333f,
    -0.1f, -0.183333f,
    0.1f, -0.133333f,
    0.1f, -0.183333f,
};
