#include "ParticleSystem.h"
#include "../Core/InstancedMesh.h"
#include <iostream>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> position_dist(-POSITION_RANGE + 5, POSITION_RANGE - 5);
std::uniform_real_distribution<float> velocity_dist(-1, 1);

static std::vector<Particle> generateParticles()
{
	std::vector<Particle> particles(PARTICLE_COUNT);
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		particles[i].position = glm::vec4(position_dist(gen), position_dist(gen), position_dist(gen), 0.0f);
		particles[i].prev_position = particles[i].position;
		//particles[i].velocity = glm::vec4(velocity_dist(gen), velocity_dist(gen), 0.0f, 0.0f);
	}
	return particles;
}

ParticleSystem::ParticleSystem()
	: m_particles(GL_SHADER_STORAGE_BUFFER, generateParticles().data(), PARTICLE_COUNT, GL_DYNAMIC_COPY)
{
	
	m_particles.sendToGpu(0);
	//m_mesh.linkAttribs(m_particles);
}

void ParticleSystem::render(const Camera& camera)
{
	m_mesh.draw(camera);
}

void ParticleSystem::update()
{
	//m_mesh.updateBuffer(m_particles);
}