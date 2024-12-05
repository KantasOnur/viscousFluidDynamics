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
	m_findOffsets("findOffsets"),
	m_boxUniform(GL_UNIFORM_BUFFER, &m_box, 1, GL_DYNAMIC_DRAW),
	m_paramUniform(GL_UNIFORM_BUFFER, &sim, 1, GL_DYNAMIC_DRAW),
	m_grid(GL_SHADER_STORAGE_BUFFER, std::vector<size_t>(PARTICLE_COUNT).data(), PARTICLE_COUNT, GL_DYNAMIC_COPY),
	m_temp(GL_SHADER_STORAGE_BUFFER, std::vector<Particle>(PARTICLE_COUNT).data(), PARTICLE_COUNT, GL_DYNAMIC_COPY),
	m_startsAt(GL_SHADER_STORAGE_BUFFER, std::vector<unsigned int>(PARTICLE_COUNT).data(), PARTICLE_COUNT, GL_DYNAMIC_COPY)
{
	m_boxUniform.sendToGpu(1);
	m_paramUniform.sendToGpu(2);
	m_grid.sendToGpu(3);
	m_temp.sendToGpu(4);
	m_startsAt.sendToGpu(5);
}

void ParticleSimulation::step()
{
	const size_t threadsPerBlock = 1024;
	const size_t numBlocks = (threadsPerBlock + PARTICLE_COUNT - 1) / threadsPerBlock;

	// apply gravity also builds the grid
	m_applyGravity.dispatch(numBlocks, 1, 1);
	_sortParticles({ numBlocks, 1, 1 });

	m_doubleDensityRelaxation.dispatch(numBlocks, 1, 1);
	m_updateVelocity.dispatch(numBlocks, 1, 1);

	ImGui::Begin("Fluid Parameters");
	ImGui::SliderFloat3("Gravity", reinterpret_cast<float*>(&sim.gravity), -10, 10);
	ImGui::SliderFloat("Time Step", &sim.dt, 0.001f, 0.01f);
	ImGui::SliderFloat("Interaction Radius", &sim.h, 0.01f, 1.0f);
	ImGui::SliderFloat("Rest Density", &sim.restDensity, 0.0f, 40.0f);
	ImGui::SliderFloat("Pressure", &sim.k, 1.0f, 10.0f);
	ImGui::SliderFloat("Surface Tension", &sim.nearK, 0.0f, 10.0f);
	m_paramUniform.updateBuffer(&sim);
	ImGui::End();


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

void ParticleSimulation::_sortParticles(const glm::vec3& grid)
{
	std::vector<Particle> particles(PARTICLE_COUNT);
	std::vector<unsigned int> startsAt(PARTICLE_COUNT);

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
	m_findOffsets.dispatch(grid.x, grid.y, grid.z);
	/*
	m_startsAt.retrieveBuffer(0, PARTICLE_COUNT, startsAt.data());
	m_target->m_particles.retrieveBuffer(0, PARTICLE_COUNT, particles.data());
	
	for (int i = 0; i < PARTICLE_COUNT - 1; ++i)
	{
		assert(particles[i].cellID.x <= particles[i + 1].cellID.x);
	}
	
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		std::cout << particles[i].cellID.x << " ";
	}
	
	std::cout << std::endl << "--------------------" << std::endl;
	

	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		std::cout << startsAt[i] << " ";
	}
	std::cout << std::endl;
	*/
}