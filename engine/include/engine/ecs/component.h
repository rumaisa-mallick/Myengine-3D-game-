#pragma once

#include "engine/math/math_utils.h"
#include <cstdint>
#include <string>
#include <typeindex>

namespace engine {

using ComponentType = uint32_t;
constexpr ComponentType INVALID_COMPONENT = 0;

inline ComponentType next_component_type() {
    static ComponentType type = 0;
    return ++type;
}

template<typename T>
ComponentType get_component_type() {
    static ComponentType type = next_component_type();
    return type;
}

struct Component {
    virtual ~Component() = default;
};

struct TransformComponent : public Component {
    Vec3 position;
    Vec3 rotation;
    Vec3 scale = Vec3::one();

    TransformComponent() = default;
    TransformComponent(Vec3 pos, Vec3 rot = {}, Vec3 sc = Vec3::one())
        : position(pos), rotation(rot), scale(sc) {}
};

struct TagComponent : public Component {
    std::string tag;

    TagComponent() = default;
    TagComponent(const std::string& t) : tag(t) {}
};

} // namespace engine
