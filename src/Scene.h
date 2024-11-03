#pragma once
#include <vector>
#include "Core/Mesh.h"
#include "Core/Camera.h"
#include "Systems/ParticleSystem.h"
#include "Systems/ParticleSimulation.h"

class Scene
{
private:
    ParticleSystem m_particleSys;
    ParticleSimulation m_particleSim;
    std::unique_ptr<Camera> camera_;
public:
    Scene(const Window& window);
    void render();
};
