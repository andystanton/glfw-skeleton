#include <bandit/bandit.h>

#include "util/shaderhelper.hpp"

using namespace bandit;

go_bandit([]() {
    describe("the shader helper", []() {
        it("loads shader code from files", [&]() {
            const string expected = "\n"
                    "#version 330 core\n"
                    "\n"
                    "layout(location = 0) in vec2 vertexPosition_modelspace;\n"
                    "\n"
                    "uniform mat4    mvp;\n"
                    "uniform vec2    position;\n"
                    "uniform float   scale;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "    gl_Position = mvp * vec4(vertexPosition_modelspace * scale + position, 0, 1);\n"
                    "}";

            const string actual = shaderhelper::loadShader("fixtures/shaders/2dcolor.vert");
            AssertThat(actual, Is().EqualTo(expected));
        });
    });
});
