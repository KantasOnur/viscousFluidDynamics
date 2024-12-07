struct Particle
{
    vec4 position; // 4th component of position is the cellID 
    vec4 prev_position;
    vec4 next_position;
    vec4 velocity;
    ivec4 cellID;
};


struct BoundingBox
{
    vec4 bounds[6];
    vec4 normals[6];
    vec4 scale;
    vec4 rotation;
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

layout(std430, binding = 5) buffer StartsAt
{
    uint startsAt[];
};

vec3 findCell(inout Particle p)
{
    float spacing = 2.0f * sim.h;
    int x = int(floor(p.position.x / spacing));
    int y = int(floor(p.position.y / spacing));
    int z = int(floor(p.position.z / spacing));
    return vec3(x, y, z);
}

int hash(inout Particle p)
{
    vec3 cell_coords = findCell(p);
    // psuedo-random, subtracting by a large negative number so the function doesnt return the same value for mirrored coords.
    int h = (int(cell_coords.x * 30945845) ^ int(cell_coords.y * 345897) ^ int(cell_coords.z * 897543)) - 23498239;
    return abs(h) % sim.particleCount;
}

int hash(inout vec3 cell_coords)
{
    int h = (int(cell_coords.x * 30945845) ^ int(cell_coords.y * 345897) ^ int(cell_coords.z * 897543)) - 23498239;
    return abs(h) % sim.particleCount;
}
