#include "Scene.h"
#include "Core/Mesh.h"
#include <memory>
#include "Systems/ParticleSystem.h"
Scene::Scene(const Window& window)
    : m_particleSim(&m_particleSys)
{
    camera_ = std::make_unique<Camera>(window);
}

void Scene::render()
{

    m_particleSys.render(*camera_);
    m_particleSim.step();

    /*
    for (auto& object: m_objects)
    {
        object->render(*camera_);
    }
    */
}