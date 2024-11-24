#pragma once
#include "ParticleSystem.h"
#include "../Core/SquareMesh.h"
#include "../Core/ComputeShader.h"
#include "../Core/OpenGLBuffer.h"

class ParticleSimulation : BaseObject
{
private:
	struct Params
	{
		glm::vec4 gravity = { 0.0f, -9.81f, 0.0f, 0.0f };
		float dt = 0.01f;
		float h = 0.65f;
		float restDensity = 14.0f;
		float k = 7.0f;
		float nearK = 30.0f;
		int particleCount = PARTICLE_COUNT;
		int boxHeight = 2 * POSITION_RANGE;
	};

	struct BoundingBox
	{
		glm::vec4 bounds[4] =
		{																// Vertices		// Bounding planes
			{-POSITION_RANGE,  POSITION_RANGE, -POSITION_RANGE, 0.0f},	// Top left		// Left plane
			{-POSITION_RANGE, -POSITION_RANGE, -POSITION_RANGE, 0.0f},	// Bottom left	// Bottom plane
			{POSITION_RANGE, POSITION_RANGE, -POSITION_RANGE, 0.0f},	// Top right	// Top plane
			{POSITION_RANGE, -POSITION_RANGE, -POSITION_RANGE, 0.0f}	// Bottom right	// Right plane
		};
		glm::vec4 normals[4]
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, -1.0f, 0.0f, 0.0f},
			{-1.0f, 0.0f, 0.0f, 0.0f}
		};
	};
private:

	ParticleSystem* m_target;
	Params sim;
	BoundingBox m_box;
	
	ComputeShader m_resetGrid;
	ComputeShader m_applyGravity;
	ComputeShader m_updateVelocity;
	ComputeShader m_doubleDensityRelaxation;
	ComputeShader m_partialSort;
	ComputeShader m_merge;

	OpenGLBuffer<BoundingBox> m_boxUniform;
	OpenGLBuffer<Params> m_paramUniform;
	OpenGLBuffer<size_t> m_grid;
	OpenGLBuffer<Particle> m_temp; // Used when sorting the particles
	//OpenGLBuffer<int> m_startIndices;

private:
	void resolveCollisions(Particle* particles);
	void doubleDensityRelaxation(Particle* particles);
	void _sortParticles(const glm::vec3& grid);
public:
	ParticleSimulation(ParticleSystem* target);
	void render(const Camera& camera) override;
	void step();


private:
	
	std::vector<Vertex> m_vertices =
	{
		m_box.bounds[0],
		m_box.bounds[1],
		m_box.bounds[2],
		m_box.bounds[3]
	};
	
	std::vector<Index> m_indices = { 0, 1, 2, 2, 3, 1 };
	Mesh m_boundingBoxMesh = Mesh(m_vertices, m_indices, "boundingBox");
};

