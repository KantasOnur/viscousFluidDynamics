struct Particle
{
    vec4 position;
    vec4 prev_position;
    vec4 next_position;
    vec4 velocity;
};

struct BoundingBox
{
    vec4 bounds[4];
    vec4 normals[4];
};

struct Params
{

    vec4 gravity;
    float dt;
    float h;
    float restDensity;
    float k;
    float nearK;
    int particleCount;
};

layout(std430, binding = 0) buffer ParticleBuffer {
    Particle particles[];
};

layout(std140, binding = 1) uniform BoxUniform
{
    BoundingBox box;
};

layout(std140, binding = 2) uniform ParamsUniform
{
    Params sim;
};