#pragma once

#include "engine/ecs/world.h"
#include <string>
#include <memory>

namespace engine {

class Scene {
public:
    Scene(const std::string& name = "Untitled");
    ~Scene();

    const std::string& get_name() const { return m_name; }
    void set_name(const std::string& name) { m_name = name; }

    World& get_world() { return m_world; }
    const World& get_world() const { return m_world; }

    void on_enter();
    void on_exit();
    void update(float dt);

private:
    std::string m_name;
    World m_world;
    bool m_active = false;
};

} // namespace engine
