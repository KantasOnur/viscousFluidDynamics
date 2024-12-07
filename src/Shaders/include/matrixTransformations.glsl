mat4 rotationX(float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);

    return mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cosTheta, -sinTheta, 0.0,
        0.0, sinTheta, cosTheta, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}
mat4 rotationY(float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);

    return mat4(
        cosTheta, 0.0, sinTheta, 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sinTheta, 0.0, cosTheta, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}
mat4 rotationZ(float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);

    return mat4(
        cosTheta, -sinTheta, 0.0, 0.0,
        sinTheta, cosTheta, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

mat4 scale(vec3 s)
{
    return mat4(
        s.x, 0.0, 0.0, 0.0,
        0.0, s.y, 0.0, 0.0,
        0.0, 0.0, s.z, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

mat4 translate(vec3 t)
{
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
        s, 0.0, 0.0, 0.0,
        0.0, s, 0.0, 0.0,
        0.0, 0.0, s, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}