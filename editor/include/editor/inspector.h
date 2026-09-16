#pragma once

#include "engine/engine.h"

namespace editor {

class Inspector {
public:
    void draw(engine::World& world, engine::Entity selected);

private:
    void draw_transform_component(engine::TransformComponent& transform);
    void draw_tag_component(engine::TagComponent& tag);
    void draw_rigid_body_component(engine::RigidBody& rb);
    void draw_collider_component(engine::Collider& collider);
};

} // namespace editor
