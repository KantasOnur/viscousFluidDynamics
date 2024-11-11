#pragma once
#include "ParticleSystem.h"
#include "../Core/SquareMesh.h"
#include "../Core/ComputeShader.h"

class ParticleSimulation : BaseObject
{
private:
	struct Params
	{
		glm::vec3 gravity = { 0.0f, -9.81f, 0.0f };
		float dt = 0.01f;
		float h = 0.65f;
		float restDensity = 40.0f;
		float k = 2.0f;
		float nearK = 30.0f;
	};

	struct BoundingBox
	{
		glm::vec3 bounds[4] =
		{														// Vertices		// Bounding planes
			{-POSITION_RANGE,  POSITION_RANGE, -POSITION_RANGE}, // Top left		// Left plane
			{-POSITION_RANGE, -POSITION_RANGE, -POSITION_RANGE}, // Bottom left	// Bottom plane
			{POSITION_RANGE, POSITION_RANGE, -POSITION_RANGE},	  // Top right		// Top plane
			{POSITION_RANGE, -POSITION_RANGE, -POSITION_RANGE}   // Bottom right	// Right plane
		};
		glm::vec3 normals[4]
		{
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, -1.0f, 0.0f},
			{-1.0f, 0.0f, 0.0f}
		};
	};
private:

	ParticleSystem* m_target;
	Params sim;
	BoundingBox m_box;

	ComputeShader m_applyGravity;
private:
	void resolveCollisions(Particle* particles);
	void doubleDensityRelaxation(Particle* particles);
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

