#version 330 core

layout(location = 0) in vec2 attribute_pos;

void main() {
    gl_Position = vec4(attribute_pos, 0.0, 1.0);
}
