#include "editor/inspector.h"

namespace editor {

void Inspector::draw(engine::World& world, engine::Entity selected) {
    if (selected == engine::NULL_ENTITY) return;

    auto* tag = world.get_component<engine::TagComponent>(selected);
    if (tag) draw_tag_component(*tag);

    auto* transform = world.get_component<engine::TransformComponent>(selected);
    if (transform) draw_transform_component(*transform);

    auto* rb = world.get_component<engine::RigidBody>(selected);
    if (rb) draw_rigid_body_component(*rb);

    auto* collider = world.get_component<engine::Collider>(selected);
    if (collider) draw_collider_component(*collider);
}

void Inspector::draw_transform_component(engine::TransformComponent& transform) {
    // ImGui transform widget
}

void Inspector::draw_tag_component(engine::TagComponent& tag) {
    // ImGui tag input
}

void Inspector::draw_rigid_body_component(engine::RigidBody& rb) {
    // ImGui rigid body properties
}

void Inspector::draw_collider_component(engine::Collider& collider) {
    // ImGui collider properties
}

} // namespace editor
