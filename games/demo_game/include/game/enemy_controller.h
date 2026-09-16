#pragma once

#include "engine/engine.h"

namespace game {

struct EnemyController : public engine::Component {
    float move_speed = 2.0f;
    float detection_range = 10.0f;
    float attack_range = 2.0f;
    engine::Entity target = engine::NULL_ENTITY;
};

class EnemySystem : public engine::System {
public:
    void update(engine::World& world, float dt) override;
    const char* get_name() const override { return "EnemySystem"; }
};

} // namespace game
