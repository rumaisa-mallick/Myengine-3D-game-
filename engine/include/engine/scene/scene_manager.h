#pragma once

#include "engine/scene/scene.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

namespace engine {

class SceneManager {
public:
    static SceneManager& instance();

    std::shared_ptr<Scene> create_scene(const std::string& name);
    void load_scene(const std::string& name);
    void unload_scene(const std::string& name);

    std::shared_ptr<Scene> get_current_scene() const { return m_current; }
    std::shared_ptr<Scene> get_scene(const std::string& name) const;

    void update(float dt);

    using SceneChangeCallback = std::function<void(const std::string&)>;
    void on_scene_change(SceneChangeCallback callback) { m_callback = callback; }

private:
    SceneManager() = default;
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
    std::shared_ptr<Scene> m_current;
    SceneChangeCallback m_callback;
};

} // namespace engine
