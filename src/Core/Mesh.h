#pragma once
#include "../Core/Shader.h"
#include <glm/glm.hpp>
#include "../Core/Camera.h"
#include <memory>

using Vertex = glm::vec3;
using Index = unsigned int;
class Mesh
{
protected:
    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
    Shader shader_;
    unsigned int vao_, vbo_, ibo_;
    void initBuffers();
public:
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices_, const std::vector<Index>& indices_, 
        const std::string& shader);
    ~Mesh();
    virtual void draw(const Camera& camera);
    Shader* getShader() { return &shader_; };
};