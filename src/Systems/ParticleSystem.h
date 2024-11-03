#pragma once
#include "BaseSystem.h"
#define PARTICLE_COUNT 2
#include "../Core/InstancedMesh.h"


struct Particle
{
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 prev_position = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0.0f);
};

class ParticleSystem : public BaseSystem
{
	friend class ParticleSimulation;

private:
	Particle m_particles[PARTICLE_COUNT];

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