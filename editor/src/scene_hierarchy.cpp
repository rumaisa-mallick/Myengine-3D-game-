#include "editor/scene_hierarchy.h"

namespace editor {

void SceneHierarchy::draw(engine::World& world, engine::Entity& selected) {
    auto entities = world.query<engine::TagComponent>();
    for (auto entity : entities) {
        draw_entity_node(world, entity, selected);
    }
}

void SceneHierarchy::draw_entity_node(engine::World& world, engine::Entity entity, engine::Entity& selected) {
    auto* tag = world.get_component<engine::TagComponent>(entity);
    if (!tag) return;

    bool is_selected = (entity == selected);
    if (is_selected) {
        // Highlight selected entity
    }

    if (tag->tag.empty()) {
        // Display "Entity #id" if no tag
    }

    if (is_selected) {
        selected = entity;
    }
}

} // namespace editor
