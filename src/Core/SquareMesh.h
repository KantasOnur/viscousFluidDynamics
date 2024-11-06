#pragma once
#include "Mesh.h"
class SquareMesh : public Mesh
{
private:
	std::vector<Vertex> m_vertices =
	{
		{-0.5f,  0.5f, 0.0f}, // Top left
			{-0.5f, -0.5f, 0.0f}, // Bottom Left
			{0.5f, 0.5f, 0.0f}, // Top right
			{0.5f, -0.5f, 0.0f} // Bottom right
	};
	std::vector<Index> m_indices = { 0, 1, 2, 2, 3, 1 };
public:
	SquareMesh(const std::string& shader);
};

