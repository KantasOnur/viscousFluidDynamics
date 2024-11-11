#include "InstancedMesh.h"
#include "../Systems/ParticleSystem.h"

InstancedMesh::InstancedMesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices,
	const std::string& shader, const size_t& count)
	: Mesh(vertices, indices, shader), m_count(count)
{ }

void InstancedMesh::linkAttribs(const void* instancedObjects)
{
    const Particle* p = static_cast<const Particle*>(instancedObjects);

    glBindVertexArray(vao_);
    glGenBuffers(1, &m_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * m_count, p, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);
    glBindVertexArray(0);
}

void InstancedMesh::updateBuffer(const void* instancedObjects)
{
    const Particle* p = static_cast<const Particle*>(instancedObjects);
    glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * m_count, p);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstancedMesh::draw(const Camera& camera)
{
    shader_.bind();
    shader_.setMatrix4f("projectionMatrix", camera.getProjection());
    shader_.setMatrix4f("viewMatrix", camera.getView());
    shader_.setVec3f("viewPos", camera.getPosition());
    glBindVertexArray(vao_);
    glDrawElementsInstanced(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr, m_count);
    glBindVertexArray(0);
    shader_.unbind();
}