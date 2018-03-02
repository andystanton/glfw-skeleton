#version 330 core

uniform vec4 uniform_color;
out vec4 outputColor;

void main()
{
	outputColor = uniform_color;
}
