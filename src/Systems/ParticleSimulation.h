#pragma once
#include "ParticleSystem.h"
#include "../Core/SquareMesh.h"

class ParticleSimulation : BaseObject
{
private:
	struct Params
	{
		glm::vec3 gravity = { 0.0f,-9.81f, 0.0f };
		float dt = 0.0001f;
		float h = 1.0f;
		float restDensity = 1.0f;
		float k = 1.0f;
		float nearK = 0.5f;
	};

	struct BoundingBox
	{
		glm::vec3 bounds[4] =
		{						  // Vertices		// Bounding planes
			{-0.4f,  0.4f, 0.0f}, // Top left		// Left plane
			{-0.4f, -0.4f, 0.0f}, // Bottom left	// Bottom plane
			{0.4f, 0.4f, 0.0f},	  // Top right	// Top plane
			{0.4f, -0.4f, 0.0f}   // Bottom right	// Right plane
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

