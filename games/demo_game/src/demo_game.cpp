#include "game/demo_game.h"
#include "game/player_controller.h"
#include "game/enemy_controller.h"
#include "game/game_hud.h"

namespace game {

DemoGame::DemoGame() : engine::Application(engine::AppConfig{"Demo Game", 1280, 720}) {
}

DemoGame::~DemoGame() = default;

void DemoGame::on_init() {
    m_renderer.init();

    m_game_scene = engine::SceneManager::instance().create_scene("Game Level");
    auto& world = m_game_scene->get_world();

    world.add_system<PlayerSystem>();
    world.add_system<EnemySystem>();

    m_player = world.create_entity();
    world.add_component<engine::TagComponent>(m_player, engine::TagComponent{"Player"});
    world.add_component<engine::TransformComponent>(m_player, engine::TransformComponent{{0, 0, 0}});
    world.add_component<PlayerController>(m_player);

    auto enemy = world.create_entity();
    world.add_component<engine::TagComponent>(enemy, engine::TagComponent{"Enemy"});
    world.add_component<engine::TransformComponent>(enemy, engine::TransformComponent{{5, 0, 0}});
    world.add_component<EnemyController>(enemy);

    auto ground = world.create_entity();
    world.add_component<engine::TagComponent>(ground, engine::TagComponent{"Ground"});
    world.add_component<engine::TransformComponent>(ground, engine::TransformComponent{{0, -1, 0}, {0, 0, 0}, {20, 1, 20}});

    engine::SceneManager::instance().load_scene("Game Level");

    m_camera.set_position({0, 5, 10});
    m_camera.look_at({0, 0, 0});

    LOG_INFO("Demo game initialized");
}

void DemoGame::on_update(float dt) {
    engine::SceneManager::instance().update(dt);
}

void DemoGame::on_render() {
    m_renderer.begin_frame();

    auto& world = m_game_scene->get_world();
    auto entities = world.query<engine::TransformComponent>();

    for (auto entity : entities) {
        auto* transform = world.get_component<engine::TransformComponent>(entity);
        if (!transform) continue;

        engine::Mat4 model = engine::Mat4::translate(transform->position) *
                            engine::Mat4::rotate_y(engine::math::to_radians(transform->rotation.y)) *
                            engine::Mat4::scale(transform->scale);

        engine::RenderCommand cmd;
        cmd.transform = model;
        m_renderer.submit(cmd);
    }

    m_renderer.end_frame();
}

void DemoGame::on_shutdown() {
    m_renderer.shutdown();
    LOG_INFO("Demo game shut down");
}

} // namespace game

int main() {
    game::DemoGame game;
    game.run();
    return 0;
}
