#pragma once

#include "engine/math/math_utils.h"
#include "engine/physics/rigid_body.h"
#include "engine/physics/collider.h"
#include <cstdint>
#include <vector>
#include <functional>

namespace engine {

struct CollisionInfo {
    uint32_t entity_a;
    uint32_t entity_b;
    Vec3 normal;
    float penetration;
};

class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld();

    void set_gravity(Vec3 gravity) { m_gravity = gravity; }
    Vec3 get_gravity() const { return m_gravity; }

    void update(float dt);

    using CollisionCallback = std::function<void(const CollisionInfo&)>;
    void on_collision(CollisionCallback callback) { m_collision_callback = callback; }

private:
    Vec3 m_gravity = {0, -9.81f, 0};
    CollisionCallback m_collision_callback;

    void integrate(float dt);
    void detect_collisions();
    void resolve_collisions();
};

} // namespace engine
