#include "game/enemy_controller.h"
#include "game/player_controller.h"
#include <cmath>

namespace game {

void EnemySystem::update(engine::World& world, float dt) {
    auto entities = world.query<EnemyController, engine::TransformComponent>();

    for (auto entity : entities) {
        auto* controller = world.get_component<EnemyController>(entity);
        auto* transform = world.get_component<engine::TransformComponent>(entity);
        if (!controller || !transform) continue;

        if (controller->target == engine::NULL_ENTITY) {
            auto players = world.query<PlayerController>();
            if (!players.empty()) {
                controller->target = players[0];
            }
        }

        if (controller->target != engine::NULL_ENTITY) {
            auto* target_transform = world.get_component<engine::TransformComponent>(controller->target);
            if (target_transform) {
                engine::Vec3 dir = target_transform->position - transform->position;
                float dist = dir.length();

                if (dist < controller->detection_range && dist > controller->attack_range) {
                    dir = dir.normalized();
                    transform->position += dir * controller->move_speed * dt;

                    float angle = std::atan2(dir.x, dir.z) * engine::RAD_TO_DEG;
                    transform->rotation.y = angle;
                }
            }
        }
    }
}

} // namespace game
