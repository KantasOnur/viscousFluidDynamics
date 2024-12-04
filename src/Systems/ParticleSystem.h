#pragma once
#include "BaseSystem.h"
#define PARTICLE_COUNT (1 << 16)
#define POSITION_RANGE 20.0f
#include "../Core/InstancedMesh.h"
#include "../Core/OpenGLBuffer.h"

struct Particle
{
	glm::vec4 position = glm::vec4(0.0f);
	glm::vec4 prev_position = glm::vec4(0.0f);
	glm::vec4 next_position = glm::vec4(0.0f);
	glm::vec4 velocity = glm::vec4(0.0f);
	glm::ivec4 cellID = glm::vec4(0.0f);
};

class ParticleSystem : public BaseSystem
{
	friend class ParticleSimulation;

private:
	//Particle m_particles[PARTICLE_COUNT];
	OpenGLBuffer<Particle> m_particles;

	std::vector<Vertex> m_vertices =
	{
		{-0.01f,  0.01f, 0.0f}, // Top left
		{-0.01f, -0.01f, 0.0f}, // Bottom Left
		{0.01f, 0.01f, 0.0f}, // Top right
		{0.01f, -0.01f, 0.0f} // Bottom right
	};

	std::vector<Index> m_indices =
	{
		0, 1, 2,
		2, 3, 1
	};

	InstancedMesh m_mesh = InstancedMesh(m_vertices, m_indices, "basic", PARTICLE_COUNT);
public:
	ParticleSystem();
	void getState(void* state) const override {};
	void setState(void* state) override {};
	void render(const Camera& camera) override;
	void update();
};