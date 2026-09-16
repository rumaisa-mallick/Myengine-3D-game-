#pragma once

#include "engine/ecs/entity.h"
#include <vector>
#include <memory>

namespace engine {

class World;

class System {
public:
    virtual ~System() = default;
    virtual void update(World& world, float dt) = 0;
    virtual const char* get_name() const = 0;
};

} // namespace engine
