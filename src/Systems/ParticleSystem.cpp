#include "ParticleSystem.h"
#include "../Core/InstancedMesh.h"

ParticleSystem::ParticleSystem()
{
	m_particles[1].position = { 0.5f, 0.0f, 0.0f };
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