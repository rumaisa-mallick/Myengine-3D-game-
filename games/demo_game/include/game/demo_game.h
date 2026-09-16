#pragma once

#include "engine/engine.h"

namespace game {

class DemoGame : public engine::Application {
public:
    DemoGame();
    ~DemoGame() override;

protected:
    void on_init() override;
    void on_update(float dt) override;
    void on_render() override;
    void on_shutdown() override;

private:
    engine::Renderer m_renderer;
    engine::Camera m_camera;
    std::shared_ptr<engine::Scene> m_game_scene;
    engine::Entity m_player = engine::NULL_ENTITY;
};

} // namespace game
