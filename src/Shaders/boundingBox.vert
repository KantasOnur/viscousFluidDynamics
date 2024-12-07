#version 430 core
#include <common>
#include <matrixTransformations>

layout (location = 0) in vec3 vertexPosition;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;


void main()
{
    mat4 model = rotationX(box.rotation.x) * rotationY(box.rotation.y) * rotationY(box.rotation.z);
    model *= scale(box.scale.xyz);
	gl_Position = projectionMatrix * viewMatrix * model * vec4(vertexPosition, 1.0);
}