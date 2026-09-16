#include "game/player_controller.h"
#include <cmath>

namespace game {

void PlayerSystem::update(engine::World& world, float dt) {
    auto entities = world.query<PlayerController, engine::TransformComponent>();
    auto& input = engine::Input::instance();

    for (auto entity : entities) {
        auto* controller = world.get_component<PlayerController>(entity);
        auto* transform = world.get_component<engine::TransformComponent>(entity);
        if (!controller || !transform) continue;

        engine::Vec3 movement;
        if (input.is_key_pressed(engine::KeyCode::W)) movement.z -= 1;
        if (input.is_key_pressed(engine::KeyCode::S)) movement.z += 1;
        if (input.is_key_pressed(engine::KeyCode::A)) movement.x -= 1;
        if (input.is_key_pressed(engine::KeyCode::D)) movement.x += 1;

        if (movement.length_sq() > 0) {
            movement = movement.normalized() * controller->move_speed * dt;
            transform->position += movement;
        }

        if (input.is_key_just_pressed(engine::KeyCode::Space) && controller->is_grounded) {
            auto* rb = world.get_component<engine::RigidBody>(entity);
            if (rb) {
                rb->apply_impulse({0, controller->jump_force, 0});
                controller->is_grounded = false;
            }
        }
    }
}

} // namespace game
