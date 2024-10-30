#pragma once
#include <vector>
#include "Core/Mesh.h"
#include "Core/Camera.h"

class Scene
{
private:
    std::vector<std::unique_ptr<Mesh>> meshes_;
    std::unique_ptr<Camera> camera_;
public:
    Scene(const Window& window);
    void render();
};
