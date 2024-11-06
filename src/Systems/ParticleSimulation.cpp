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
		particle.acceleration = sim.gravity;
	}
	
	for (auto& particle : particles)
	{
		particle.prev_position = particle.position;
		particle.position += sim.dt * particle.velocity;
	}

	//doubleDensityRelaxation(particles);
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
	float density;
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		density = 0.0f;
		pressure = 0.0f;
		for (int j = 0; j < PARTICLE_COUNT; ++j)
		{
			if (j == i) break;
			particleDistance = glm::distance(particles[j].position, particles[i].position);
			if (particleDistance < sim.h)
			{
				density += glm::pow(1 - particleDistance / sim.h, 2);
			}
		}
		pressure = sim.k * (density - sim.restDensity);
	}
}
void ParticleSimulation::resolveCollisions(Particle* particles)
{
	glm::vec3 forceSpring;
	glm::vec3 forceDamping;
	glm::vec3 forceNormal;
	glm::vec3 forceTangent; 

	glm::vec3 normal;
	float dirDotN;
	const float ks = 100.0f;
	const float kd = 300.0f;
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		Particle& p = particles[i];
		for (int j = 0; j < 4; ++j)
		{
			normal = m_box.normals[j];
			dirDotN = glm::dot(p.position - m_box.bounds[j], normal);
			if (dirDotN < 0)
			{

				glm::vec3 line = p.position - p.prev_position;
				float ratio = glm::dot(line, normal) / -dirDotN;
				glm::vec3 intersection = p.prev_position + line * ratio;

				/* This might be a bad idea. */
				p.position -= dirDotN * normal;
				p.prev_position = p.position;

				forceDamping = -kd * (glm::dot(p.velocity, line)) * line / glm::pow(glm::length(line), 2.0f);
				forceSpring = -ks * line + forceDamping;
				forceNormal = glm::dot(forceSpring, normal) * normal;
				forceTangent = forceSpring - forceNormal;
				forceTangent = glm::length(forceTangent) > glm::length(forceNormal) ? forceNormal : forceTangent;

				glm::vec3 force = forceSpring + forceNormal + forceTangent;

				
				//p.position += glm::reflect(p.velocity, normal) * sim.dt;
				p.velocity += force * sim.dt;
				p.position += glm::reflect(p.velocity, normal) * sim.dt;
			}
		}
	}
}