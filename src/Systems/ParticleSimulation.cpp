#include "ParticleSimulation.h"
#include <iostream>

ParticleSimulation::ParticleSimulation(ParticleSystem* target)
	: m_target(target) 
{
	
}

void ParticleSimulation::step()
{
	auto& particles = m_target->m_particles;
	for (auto& particle : particles)
	{
		particle.velocity += sim.dt * sim.gravity;
	}

	for (auto& particle : particles)
	{
		particle.prev_position = particle.position;
		particle.position += particle.velocity * sim.dt;
	}


	doubleDensityRelaxation(particles);
	resolveCollisions(particles);
	for (auto& particle : particles)
	{
		particle.velocity = (particle.position - particle.prev_position) / sim.dt;
	}
	m_target->update();
}


void ParticleSimulation::render(const Camera& camera)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_boundingBoxMesh.draw(camera);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ParticleSimulation::doubleDensityRelaxation(Particle* particles)
{

	std::vector<glm::vec3> position_updated(PARTICLE_COUNT);

	float particleDistance;
	float pressure;
	float pressure_near;
	float density;
	float density_near;

	float weightedContribution;
	glm::vec3 dx;

	glm::vec3 displacement;

	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		density = 0.0f;
		density_near = 0.0f;

		// Compute density and near-density
		for (int j = 0; j < PARTICLE_COUNT; ++j)
		{
			if (i == j) continue;

			weightedContribution = glm::distance(particles[i].position, particles[j].position) / sim.h;
			if (weightedContribution < 1)
			{
				density += glm::pow(1 - weightedContribution, 2.0f);
				density_near += glm::pow(1 - weightedContribution, 3.0f);
			}
		}

		// Compute pressure and near-pressure
		pressure = sim.k * (density - sim.restDensity);
		pressure_near = sim.nearK * density_near;

		dx = { 0.0f, 0.0f, 0.0f };

		// Apply displacements
		for (int j = 0; j < PARTICLE_COUNT; ++j)
		{
			if (i == j) continue;

			weightedContribution = glm::distance(particles[i].position, particles[j].position) / sim.h;
			if (weightedContribution < 1)
			{
				displacement = glm::pow(sim.dt, 2.0f) *
					(pressure * (1 - weightedContribution) +
						pressure_near * glm::pow(1 - weightedContribution, 2.0f)) *
					glm::normalize(particles[j].position - particles[i].position);

				dx += -0.5f * displacement;
			}
		}

		position_updated[i] =  particles[i].position + dx;
	}
	
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		particles[i].position = position_updated[i];
	}
	
}
void ParticleSimulation::resolveCollisions(Particle* particles)
{
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		Particle& p = particles[i];
		for (int j = 0; j < 4; ++j)
		{
			glm::vec3 normal = m_box.normals[j];
			float dirDotN = glm::dot(p.position - m_box.bounds[j], normal);
			if (dirDotN < 0)
			{
				p.position += -dirDotN * normal;
				p.prev_position = p.position;
				p.position += 0.8f * glm::reflect(p.velocity, normal) * sim.dt;
			}
		}
	}
}