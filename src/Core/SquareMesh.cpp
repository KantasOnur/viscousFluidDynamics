#include "SquareMesh.h"
SquareMesh::SquareMesh(const std::string& shader)
	: Mesh(m_vertices, m_indices, shader) {}