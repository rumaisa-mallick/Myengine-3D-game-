#pragma once

#include "engine/math/math_utils.h"

namespace engine {

enum class ColliderType {
    Box,
    Sphere
};

struct Collider {
    ColliderType type = ColliderType::Sphere;
    Vec3 offset;
    Vec3 half_extents;
    float radius = 0.5f;
};

} // namespace engine
