#version 430 core
#include <common>

in vec3 vColor;
out vec4 color;

void main()
{
	color = vec4(vColor, 1.0f);
}