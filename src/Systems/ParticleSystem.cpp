#include "ParticleSystem.h"
#include "../Core/InstancedMesh.h"
#include <iostream>
#include <random>
#define POSITION_RANGE 0.4f
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> position_dist(-POSITION_RANGE, POSITION_RANGE);
std::uniform_real_distribution<float> velocity_dist(-1, 1);

ParticleSystem::ParticleSystem()
{
	
	glm::vec3 startPos = { -0.0f, 0.0f, 0.0f };
	glm::vec3 endPos = { 0.0f, 0.0f, 0.0f };
	glm::vec3 step = (endPos - startPos) / (float)(PARTICLE_COUNT - 1);

	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		m_particles[i].position = glm::vec3(position_dist(gen), position_dist(gen), 0.0f);
		m_particles[i].prev_position = m_particles[i].position;
		m_particles[i].velocity = glm::vec3(velocity_dist(gen), velocity_dist(gen), 0.0f);
	}

	m_mesh.linkAttribs(m_particles);
}

void ParticleSystem::render(const Camera& camera)
{
	m_mesh.draw(camera);
}

void ParticleSystem::update()
{
	m_mesh.updateBuffer(m_particles);
}