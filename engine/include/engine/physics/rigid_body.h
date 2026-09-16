#pragma once

#include "engine/math/math_utils.h"

namespace engine {

struct RigidBody {
    Vec3 velocity;
    Vec3 acceleration;
    Vec3 force;
    float mass = 1.0f;
    float restitution = 0.5f;
    float friction = 0.3f;
    bool is_static = false;
    bool use_gravity = true;

    void apply_force(Vec3 f) { force += f; }
    void apply_impulse(Vec3 impulse) { velocity += impulse / mass; }
};

} // namespace engine
