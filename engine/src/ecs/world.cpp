#include "engine/ecs/world.h"
#include "engine/core/logger.h"

namespace engine {

World::World() {
    LOG_DEBUG("World created");
}

World::~World() {
    LOG_DEBUG("World destroyed");
}

Entity World::create_entity() {
    Entity entity = m_next_entity++;
    m_masks[entity] = ComponentMask{};
    LOG_TRACE("Entity created: %u", entity);
    return entity;
}

void World::destroy_entity(Entity entity) {
    m_components.erase(entity);
    m_masks.erase(entity);
    LOG_TRACE("Entity destroyed: %u", entity);
}

bool World::is_valid(Entity entity) const {
    return m_masks.find(entity) != m_masks.end();
}

void World::add_system(std::unique_ptr<System> system) {
    LOG_INFO("System added: %s", system->get_name());
    m_systems.push_back(std::move(system));
}

void World::update(float dt) {
    for (auto& system : m_systems) {
        system->update(*this, dt);
    }
}

size_t World::entity_count() const {
    return m_masks.size();
}

} // namespace engine
