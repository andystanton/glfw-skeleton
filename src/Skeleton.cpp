#include "Skeleton.hpp"

#include "util/camerahelper.hpp"
#include "util/colorhelper.hpp"
#include "util/shaderhelper.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Skeleton::Skeleton(const std::string & name, unsigned short width, unsigned short height)
    : context { name, width, height }
    , programId { shaderhelper::createProgram("shaders/2dcolor.vert", "shaders/2dcolor.frag") }
    , uniform_color { glGetUniformLocation(programId, "uniform_color") }
    , uniform_viewProjection { glGetUniformLocation(programId, "uniform_viewProjection") }
    , viewProjection { camerahelper::getNormalisedViewProjection(width, height) }
    , foregroundColor { colorhelper::hexToVec4(0xA3B9FF) }
    , backgroundColor { colorhelper::hexToVec4(0x577EFF) }
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * SKULL_VERTICES.size(), SKULL_VERTICES.data(), GL_STATIC_DRAW);

    GLuint attribute_pos { static_cast<GLuint>(glGetAttribLocation(programId, "attribute_pos")) };
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
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    drawSkull(foregroundColor);

    context.loop();
}

bool Skeleton::isActive()
{
    return context.isActive();
}

const std::vector<GLfloat> Skeleton::SKULL_VERTICES {
    // top of skull
    0.15f, 0.125f,
    0.15f, 0.f,
    -0.15f, 0.f,
    -0.15f, 0.125f,
    0.15f, 0.125f,
    -0.15f, 0.f,

    // left of eyes
    -0.15f, 0.f,
    -0.1f, 0.f,
    -0.15f, -0.075f,
    -0.15f, -0.075f,
    -0.1f, 0.f,
    -0.1f, -0.075f,

    // centre of eyes
    -0.025f, 0.f,
    0.025f, 0.f,
    -0.025f, -0.075f,
    -0.025f, -0.075f,
    0.025f, 0.f,
    0.025f, -0.075f,

    // right of eyes
    0.15f, 0.f,
    0.1f, 0.f,
    0.15f, -0.075f,
    0.15f, -0.075f,
    0.1f, 0.f,
    0.1f, -0.075f,

    // left of nose
    -0.15f, -0.075f,
    0.f, -0.075f,
    -0.025f, -0.1f,
    -0.025f, -0.1f,
    -0.15f, -0.1f,
    -0.15f, -0.075f,

    // right of nose
    0.f, -0.075f,
    0.15f, -0.075f,
    0.025f, -0.1f,
    0.025f, -0.1f,
    0.15f, -0.075f,
    0.15f, -0.1f,

    // jaw
    -0.075f, -0.1f,
    0.075f, -0.1f,
    -0.075f, -0.1375f,
    -0.075f, -0.1375f,
    0.075f, -0.1f,
    0.075f, -0.1375f,
};
