#version 430 core
#include <common>

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 instancePosition;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 vColor;

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

mat4 scale(float s)
{
    return mat4(
        s, 0.0,     0.0,     0.0,
        0.0, s, 0.0,     0.0,
        0.0,     0.0,     s, 0.0,
        0.0,     0.0,     0.0,     1.0
    );
}

void main()
{
    vColor = mix(vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), clamp(length(particles[gl_InstanceID].velocity), 0.0f, 10.0f) * 0.1f);
    mat4 model =  translate(particles[gl_InstanceID].position.xyz) * scale(5.0f);
	gl_Position = projectionMatrix * viewMatrix * model * vec4(vertexPosition, 1.0);
}