#include "Scene.h"
#include "Core/Mesh.h"
#include <memory>

Scene::Scene(const Window& window)
{
    std::vector<Vertex> vertices = 
    {
        {{0.0f,  0.5f, -2.0f}},
        {{-0.1f, -0.5f, -2.0f}},
        {{0.1f, -0.5f, -2.0f}}
    };

    std::vector<Index> indices = { 0, 1, 2 };

    std::unique_ptr<Mesh> triangle = std::make_unique<Mesh>(vertices, indices, std::make_unique<Shader>("src/Shaders/basic.vert", "src/Shaders/basic.frag"));
    meshes_.emplace_back(std::move(triangle));
    camera_ = std::make_unique<Camera>(window);
}

void Scene::render()
{
    for (auto& mesh : meshes_)
    {
        mesh->draw(*camera_);
    }
}