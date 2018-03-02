#version 330 core

layout(location = 0) in vec2 attribute_pos;

uniform mat4 uniform_viewProjection;
uniform vec2 uniform_offset;
uniform float uniform_scale;

void main() {
    gl_Position = uniform_viewProjection * vec4(attribute_pos * uniform_scale + uniform_offset, 0, 1);
}
