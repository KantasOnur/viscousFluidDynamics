#include "ParticleSimulation.h"
#include <iostream>
ParticleSimulation::ParticleSimulation(ParticleSystem* target)
	: m_target(target) {}

void ParticleSimulation::step()
{
	for (auto& particle : m_target->m_particles)
	{
		particle.velocity += sim.gravity * sim.dt;
		particle.position += particle.velocity * sim.dt;
	}


	m_target->update();
}