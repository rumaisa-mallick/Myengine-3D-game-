#pragma once

#include "engine/engine.h"

namespace game {

struct PlayerController : public engine::Component {
    float move_speed = 5.0f;
    float jump_force = 8.0f;
    float rotation_speed = 180.0f;
    bool is_grounded = true;
};

class PlayerSystem : public engine::System {
public:
    void update(engine::World& world, float dt) override;
    const char* get_name() const override { return "PlayerSystem"; }
};

} // namespace game
