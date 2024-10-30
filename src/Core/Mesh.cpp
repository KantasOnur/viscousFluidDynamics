#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, std::unique_ptr<Shader>&& shader)
    : vertices_(vertices), indices_(indices), shader_(std::move(shader))
{
    initBuffers();
}

void Mesh::initBuffers()
{
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ibo_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), vertices_.data(), GL_STATIC_DRAW);

    glBindVertexArray(vao_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(Index), indices_.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw(const Camera& camera)
{
    shader_->bind();
    shader_->setMatrix4f("projectionMatrix", camera.getProjection());
    shader_->setMatrix4f("viewMatrix", camera.getView());
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, (int)indices_.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    shader_->unbind();
}
