#include "Skeleton.hpp"

#include "util/colorhelper.hpp"
#include "util/shaderhelper.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Skeleton::Skeleton(const std::string & name, unsigned short width, unsigned short height)
    : context { name, width, height }
    , programId { shaderhelper::createProgram("shaders/2dcolor.vert", "shaders/2dcolor.frag") }
    , uniform_color { glGetUniformLocation(programId, "uniform_color") }
    , foregroundColor { colorhelper::hexToVec4(0xA3B9FF) }
    , backgroundColor { colorhelper::hexToVec4(0x577EFF) }
{
    GLuint attribute_pos { static_cast<GLuint>(glGetAttribLocation(programId, "attribute_pos")) };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

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

void Skeleton::loop()
{
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programId);
    glUniform4fv(uniform_color, 1, glm::value_ptr(foregroundColor));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, VERTICES_COUNT);
    glBindVertexArray(0);

    glUseProgram(0);

    context.loop();
}

bool Skeleton::isActive() const
{
    return context.isActive();
}

const GLfloat Skeleton::VERTICES[VERTICES_COUNT] {
    // top of skull
    0.225f, 0.25f,
    0.225f, 0.f,
    -0.225f, 0.f,
    -0.225f, 0.25f,
    0.225f, 0.25f,
    -0.225f, 0.f,

    // left of eyes
    -0.225f, 0.f,
    -0.15f, 0.f,
    -0.225f, -0.15f,
    -0.225f, -0.15f,
    -0.15f, 0.f,
    -0.15f, -0.15f,

    // centre of eyes
    -0.04f, 0.f,
    0.04f, 0.f,
    -0.04f, -0.15f,
    -0.04f, -0.15f,
    0.04f, 0.f,
    0.04f, -0.15f,

    // right of eyes
    0.225f, 0.f,
    0.15f, 0.f,
    0.225f, -0.15f,
    0.225f, -0.15f,
    0.15f, 0.f,
    0.15f, -0.15f,

    // left of nose
    -0.225f, -0.15f,
    0.f, -0.15f,
    -0.04f, -0.2f,
    -0.04f, -0.2f,
    -0.225f, -0.2f,
    -0.225f, -0.15f,

    // right of nose
    0.f, -0.15f,
    0.225f, -0.15f,
    0.04f, -0.2f,
    0.04f, -0.2f,
    0.225f, -0.15f,
    0.225f, -0.2f,

    // jaw
    -0.115f, -0.2f,
    0.115f, -0.2f,
    -0.115f, -0.275f,
    -0.115f, -0.275f,
    0.115f, -0.2f,
    0.115f, -0.275f,
};
