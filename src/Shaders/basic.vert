#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 instancePosition;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

mat4 translate(vec3 t)
{
    // Column major for some reason??????
    return mat4(
        vec4(1.0, 0.0, 0.0, 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(t, 1.0)
   );
}


void main()
{
	gl_Position = projectionMatrix * viewMatrix * translate(instancePosition) * vec4(vertexPosition, 1.0);
}