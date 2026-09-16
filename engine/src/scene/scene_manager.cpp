#include "engine/scene/scene_manager.h"
#include "engine/core/logger.h"

namespace engine {

SceneManager& SceneManager::instance() {
    static SceneManager s_instance;
    return s_instance;
}

std::shared_ptr<Scene> SceneManager::create_scene(const std::string& name) {
    auto scene = std::make_shared<Scene>(name);
    m_scenes[name] = scene;
    LOG_INFO("Scene created: %s", name.c_str());
    return scene;
}

void SceneManager::load_scene(const std::string& name) {
    auto it = m_scenes.find(name);
    if (it == m_scenes.end()) {
        LOG_ERROR("Scene not found: %s", name.c_str());
        return;
    }

    if (m_current) {
        m_current->on_exit();
    }

    m_current = it->second;
    m_current->on_enter();

    if (m_callback) {
        m_callback(name);
    }

    LOG_INFO("Scene loaded: %s", name.c_str());
}

void SceneManager::unload_scene(const std::string& name) {
    if (m_current && m_current->get_name() == name) {
        m_current->on_exit();
        m_current = nullptr;
    }
    m_scenes.erase(name);
    LOG_INFO("Scene unloaded: %s", name.c_str());
}

std::shared_ptr<Scene> SceneManager::get_scene(const std::string& name) const {
    auto it = m_scenes.find(name);
    return it != m_scenes.end() ? it->second : nullptr;
}

void SceneManager::update(float dt) {
    if (m_current) {
        m_current->update(dt);
    }
}

} // namespace engine
