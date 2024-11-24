struct Particle
{
    vec4 position; // 4th component of position is the cellID 
    vec4 prev_position;
    vec4 next_position;
    vec4 velocity;
    //vec4 cellID;
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
    int boxHeight;
};

struct Cell
{
    uint count;
    uint id;
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

layout(std430, binding = 3) buffer Grid
{
    uint grid[];
};

layout(std430, binding = 4) buffer Temp // Used for sorting, since cant fit particles into shared memory
{
    Particle temp[];
};

vec2 findCell(inout Particle p)
{
    float spacing = 2.0f * sim.h;
    int x = int(floor(p.position.x / spacing));
    int y = int(floor(p.position.y / spacing));

    return vec2(x, y);
}

int hash(inout Particle p)
{
    vec2 cell_coords = findCell(p);
    // psuedo-random, subtracting by a large negative number so the function doesnt return the same value for mirrored coords.
    int h = (int(cell_coords.x * 30945845) ^ int(cell_coords.y * 345897)) - 23498239;
    return abs(h) % sim.particleCount;
}

int hash(inout vec2 cell_coords)
{
    int h = (int(cell_coords.x * 30945845) ^ int(cell_coords.y * 345897)) - 23498239;
    return abs(h) % sim.particleCount;
}
