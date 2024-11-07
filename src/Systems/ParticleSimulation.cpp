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
		particle.velocity += sim.gravity * sim.dt;
	}
	
	for (auto& particle : particles)
	{
		particle.prev_position = particle.position;
		particle.position += sim.dt * particle.velocity;
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
					glm::normalize(particles[i].position - particles[j].position);

				particles[j].position += 0.5f * displacement;
				dx += -0.5f * displacement;
			}
		}

		particles[i].position += dx;
	}
	
}
void ParticleSimulation::resolveCollisions(Particle* particles)
{
	glm::vec3 forceSpring;
	glm::vec3 forceDamping;
	glm::vec3 forceNormal;
	glm::vec3 forceTangent; 
	glm::vec3 force; 

	glm::vec3 normal;
	glm::vec3 line;
	glm::vec3 intersection;
	float ratio;
	float dirDotN;
	const float ks = 100.0f;
	const float kd = 3000.0f;
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		Particle& p = particles[i];
		for (int j = 0; j < 4; ++j)
		{
			normal = m_box.normals[j];
			dirDotN = glm::dot(p.position - m_box.bounds[j], normal);
			if (dirDotN < 0)
			{
				
				line = p.position - p.prev_position;
				ratio = glm::dot(line, normal) / -dirDotN;
				intersection = p.prev_position + line * ratio;

				/* This might be a bad idea. */
				
				p.position -= dirDotN * normal; // clamp the particle
				p.prev_position = p.position;

				forceDamping = -kd * (glm::dot(p.velocity, line)) * line / glm::pow(glm::length(line), 2.0f);
				forceSpring = -ks * line + forceDamping;
				forceNormal = glm::dot(forceSpring, normal) * normal;
				forceTangent = forceSpring - forceNormal;
				forceTangent = glm::length(forceTangent) > glm::length(forceNormal) ? forceNormal : forceTangent;

				force = forceSpring + forceNormal + forceTangent;

				p.velocity += force * sim.dt;
				p.position += glm::reflect(p.velocity, m_box.normals[j]) * sim.dt;
				
			}
		}
	}
}