#version 330 core

layout(location = 0) in vec2 attribute_pos;

uniform mat4 uniform_viewProjection;

void main() {
    gl_Position = uniform_viewProjection * vec4(attribute_pos, 0.0, 1.0);
}
