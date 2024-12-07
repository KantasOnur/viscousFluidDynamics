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
		float h = 0.565f;
		float restDensity = 11.0f;
		float k = 7.8f;
		float nearK = 3.0f;
		int particleCount = PARTICLE_COUNT;
		int boxHeight = 2 * POSITION_RANGE;
	};

	struct BoundingBox
	{
		glm::vec4 bounds[6] =
		{																
			{-POSITION_RANGE,  0.0f, 0.0f, 0.0f},	// Left plane
			{0.0f, -POSITION_RANGE, 0.0f, 0.0f},	// Bottom plane
			{0.0f, POSITION_RANGE, 0.0f, 0.0f},		// Top plane
			{POSITION_RANGE, 0.0f, 0.0f, 0.0f},		// Right plane
			{0.0f, 0.0f, POSITION_RANGE, 0.0f},		// Front plane
			{0.0f, 0.0f, -POSITION_RANGE, 0.0f}		// Back plane
		};
		glm::vec4 normals[6]
		{
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, -1.0f, 0.0f, 0.0f},
			{-1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, -1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f}
		};
		glm::vec4 scale = glm::vec4(0.7f, 0.458f, 0.479f, 1.0f);
		glm::vec4 rotation = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
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
	ComputeShader m_findOffsets;

	OpenGLBuffer<BoundingBox> m_boxUniform;
	OpenGLBuffer<Params> m_paramUniform;
	OpenGLBuffer<size_t> m_grid;
	OpenGLBuffer<Particle> m_temp; // Used when sorting the particles
	OpenGLBuffer<unsigned int> m_startsAt;

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
		{-POSITION_RANGE, -POSITION_RANGE, -POSITION_RANGE}, // 0: Bottom-left-back
		{ POSITION_RANGE, -POSITION_RANGE, -POSITION_RANGE}, // 1: Bottom-right-back
		{-POSITION_RANGE,  POSITION_RANGE, -POSITION_RANGE}, // 2: Top-left-back
		{ POSITION_RANGE,  POSITION_RANGE, -POSITION_RANGE}, // 3: Top-right-back
		{-POSITION_RANGE, -POSITION_RANGE,  POSITION_RANGE}, // 4: Bottom-left-front
		{ POSITION_RANGE, -POSITION_RANGE,  POSITION_RANGE}, // 5: Bottom-right-front
		{-POSITION_RANGE,  POSITION_RANGE,  POSITION_RANGE}, // 6: Top-left-front
		{ POSITION_RANGE,  POSITION_RANGE,  POSITION_RANGE}  // 7: Top-right-front
	};
	
	std::vector<Index> m_indices = 
	{ 
		// Back face
		0, 1, 2,  // Triangle 1
		1, 3, 2,  // Triangle 2

		// Front face
		4, 6, 5,  // Triangle 1
		5, 6, 7,  // Triangle 2

		// Left face
		0, 2, 4,  // Triangle 1
		4, 2, 6,  // Triangle 2

		// Right face
		1, 5, 3,  // Triangle 1
		3, 5, 7,  // Triangle 2

		// Bottom face
		0, 4, 1,  // Triangle 1
		1, 4, 5,  // Triangle 2

		// Top face
		2, 3, 6,  // Triangle 1
		3, 7, 6   // Triangle 2
	};
	Mesh m_boundingBoxMesh = Mesh(m_vertices, m_indices, "boundingBox");
};

