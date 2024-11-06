#version 330 core

layout (location = 0) in vec3 vertexPosition;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 position;

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
	gl_Position = projectionMatrix * viewMatrix * translate(vec3(position.x, position.y, 0)) * vec4(vertexPosition, 1.0);
}