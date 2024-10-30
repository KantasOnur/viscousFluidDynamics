#version 410 core

layout (location = 0) in vec3 inPos;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
void main()
{
    gl_Position = projectionMatrix * vec4(inPos, 1.0f);
}