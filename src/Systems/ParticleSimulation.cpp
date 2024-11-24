#include "ParticleSimulation.h"
#include "../Events/EventManager.h"

#include <iostream>

ParticleSimulation::ParticleSimulation(ParticleSystem* target)
	: m_target(target),
	m_resetGrid("resetGrid"),
	m_applyGravity("applyGravity"),
	m_updateVelocity("updateVelocity"),
	m_doubleDensityRelaxation("doubleDensityRelaxation"),
	m_partialSort("partialBitonicSort"),
	m_merge("bitonicMerge"),
	m_boxUniform(GL_UNIFORM_BUFFER, &m_box, 1, GL_DYNAMIC_DRAW),
	m_paramUniform(GL_UNIFORM_BUFFER, &sim, 1, GL_DYNAMIC_DRAW),
	m_grid(GL_SHADER_STORAGE_BUFFER, std::vector<size_t>(PARTICLE_COUNT).data(), PARTICLE_COUNT, GL_DYNAMIC_COPY),
	m_temp(GL_SHADER_STORAGE_BUFFER, std::vector<Particle>(PARTICLE_COUNT).data(), PARTICLE_COUNT, GL_DYNAMIC_COPY)
{
	m_boxUniform.sendToGpu(1);
	m_paramUniform.sendToGpu(2);
	m_grid.sendToGpu(3);
	m_temp.sendToGpu(4);
}

void ParticleSimulation::step()
{
	const size_t threadsPerBlock = 1024;
	const size_t numBlocks = (threadsPerBlock + PARTICLE_COUNT - 1) / threadsPerBlock;

	// apply gravity also builds the grid
	m_applyGravity.dispatch(numBlocks, 1, 1);
	_sortParticles({ numBlocks, 1, 1 });

	//m_doubleDensityRelaxation.dispatch(numBlocks, 1, 1);
	//m_updateVelocity.dispatch(numBlocks, 1, 1);
	/*
	std::vector<Particle> particles(PARTICLE_COUNT);
	std::vector<size_t> grid(PARTICLE_COUNT);

	m_target->m_particles.retrieveBuffer(0, PARTICLE_COUNT, particles.data());
	m_grid.retrieveBuffer(0, PARTICLE_COUNT, grid.data());

	std::cout << grid[particles[0].cellID.x] << std::endl;
	*/
	//m_doubleDensityRelaxation.dispatch(numBlocks, 1, 1);
	//m_updateVelocity.dispatch(numBlocks, 1, 1);
}


void ParticleSimulation::render(const Camera& camera)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_boundingBoxMesh.draw(camera);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void ParticleSimulation::doubleDensityRelaxation(Particle* particles)
{

	/*
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
	*/
}
void ParticleSimulation::resolveCollisions(Particle* particles)
{
	/*
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
	*/
}

void ParticleSimulation::_sortParticles(const glm::vec3& grid)
{
	std::vector<Particle> particles(PARTICLE_COUNT);
	m_partialSort.dispatch(grid.x, grid.y, grid.z);
	for (unsigned int step = 1024; step <= PARTICLE_COUNT; step <<= 1)
	{
		for (unsigned int substep = step >> 1; substep > 0; substep >>= 1)
		{
			m_merge.setUInt("step", step);
			m_merge.setUInt("substep", substep);
			m_merge.dispatch(grid.x, grid.y, grid.z);
		}
	}
	/*
	m_target->m_particles.retrieveBuffer(0, PARTICLE_COUNT, particles.data());
	for (int i = 0; i < PARTICLE_COUNT - 1; ++i)
	{
		assert(particles[i].position.w <= particles[i + 1].position.w);
	} 
	
	std::cout << "here" << std::endl;
	*/
}