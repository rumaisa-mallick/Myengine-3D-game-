#pragma once

#include "engine/engine.h"
#include <string>

namespace editor {

class SceneHierarchy {
public:
    void draw(engine::World& world, engine::Entity& selected);

private:
    void draw_entity_node(engine::World& world, engine::Entity entity, engine::Entity& selected);
};

} // namespace editor
