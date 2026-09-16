#pragma once

#include "engine/ecs/entity.h"
#include "engine/ecs/component.h"
#include "engine/ecs/system.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <functional>
#include <algorithm>

namespace engine {

class World {
public:
    World();
    ~World();

    Entity create_entity();
    void destroy_entity(Entity entity);
    bool is_valid(Entity entity) const;

    template<typename T, typename... Args>
    T& add_component(Entity entity, Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        ComponentType type = get_component_type<T>();

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *component;

        m_components[entity][type] = std::move(component);
        m_masks[entity].set(type);

        return ref;
    }

    template<typename T>
    void remove_component(Entity entity) {
        ComponentType type = get_component_type<T>();
        auto entity_it = m_components.find(entity);
        if (entity_it != m_components.end()) {
            entity_it->second.erase(type);
        }
        if (m_masks.find(entity) != m_masks.end()) {
            m_masks[entity].reset(type);
        }
    }

    template<typename T>
    T* get_component(Entity entity) {
        ComponentType type = get_component_type<T>();
        auto entity_it = m_components.find(entity);
        if (entity_it != m_components.end()) {
            auto comp_it = entity_it->second.find(type);
            if (comp_it != entity_it->second.end()) {
                return dynamic_cast<T*>(comp_it->second.get());
            }
        }
        return nullptr;
    }

    template<typename T>
    bool has_component(Entity entity) const {
        ComponentType type = get_component_type<T>();
        auto mask_it = m_masks.find(entity);
        if (mask_it != m_masks.end()) {
            return mask_it->second.test(type);
        }
        return false;
    }

    template<typename... Args>
    std::vector<Entity> query() {
        ComponentMask required;
        (required.set(get_component_type<Args>()), ...);

        std::vector<Entity> result;
        for (auto& [entity, mask] : m_masks) {
            if ((mask & required) == required) {
                result.push_back(entity);
            }
        }
        return result;
    }

    template<typename T>
    void add_system() {
        m_systems.push_back(std::make_unique<T>());
    }

    void add_system(std::unique_ptr<System> system);
    void update(float dt);

    size_t entity_count() const;

private:
    Entity m_next_entity = 1;
    std::unordered_map<Entity, std::unordered_map<ComponentType, std::unique_ptr<Component>>> m_components;
    std::unordered_map<Entity, ComponentMask> m_masks;
    std::vector<std::unique_ptr<System>> m_systems;
};

} // namespace engine
