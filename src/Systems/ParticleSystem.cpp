#include "ParticleSystem.h"
#include "../Core/InstancedMesh.h"
#include <iostream>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> position_dist(-POSITION_RANGE + 2.0f, POSITION_RANGE - 2.0f);
std::uniform_real_distribution<float> velocity_dist(-1, 1);

ParticleSystem::ParticleSystem()
{
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		m_particles[i].position = glm::vec3(position_dist(gen), position_dist(gen), -POSITION_RANGE);
		m_particles[i].prev_position = m_particles[i].position;
		//m_particles[i].velocity = glm::vec3(velocity_dist(gen), velocity_dist(gen), 0.0f);
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