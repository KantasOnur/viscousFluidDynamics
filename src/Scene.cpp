#include "Scene.h"
#include "Core/Mesh.h"
#include <memory>
#include "Systems/ParticleSystem.h"
Scene::Scene(const Window& window)
    : m_particleSim(&m_particleSys)
{
    camera_ = std::make_unique<Camera>(window.getAspectRatio());
}

void Scene::render()
{
    m_particleSim.step();
    m_particleSim.render(*camera_);
    m_particleSys.render(*camera_);
}