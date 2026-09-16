#include "engine/scene/scene.h"
#include "engine/core/logger.h"

namespace engine {

Scene::Scene(const std::string& name) : m_name(name) {
    LOG_DEBUG("Scene created: %s", name.c_str());
}

Scene::~Scene() {
    LOG_DEBUG("Scene destroyed: %s", m_name.c_str());
}

void Scene::on_enter() {
    m_active = true;
    LOG_INFO("Scene entered: %s", m_name.c_str());
}

void Scene::on_exit() {
    m_active = false;
    LOG_INFO("Scene exited: %s", m_name.c_str());
}

void Scene::update(float dt) {
    if (m_active) {
        m_world.update(dt);
    }
}

} // namespace engine
