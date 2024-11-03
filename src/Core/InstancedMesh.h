#pragma once
#include "Mesh.h"
class InstancedMesh : public Mesh
{
private:
	unsigned int m_instanceVBO;
	size_t m_count;
public:
	InstancedMesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, 
		const std::string& shader, const size_t& count);
	void linkAttribs(const void* instancedObject);
	void updateBuffer(const void* instancedObjects);
	void draw(const Camera& camera) override;
};

