#include <gtest/gtest.h>
#include "engine/ecs/world.h"
#include "engine/ecs/component.h"

using namespace engine;

struct TestComponent : public Component {
    int value = 0;
    TestComponent(int v = 0) : value(v) {}
};

struct AnotherComponent : public Component {
    float data = 0.0f;
    AnotherComponent(float d = 0.0f) : data(d) {}
};

TEST(ECSTest, CreateEntity) {
    World world;
    Entity e = world.create_entity();
    EXPECT_NE(e, NULL_ENTITY);
    EXPECT_TRUE(world.is_valid(e));
}

TEST(ECSTest, DestroyEntity) {
    World world;
    Entity e = world.create_entity();
    EXPECT_TRUE(world.is_valid(e));
    world.destroy_entity(e);
    EXPECT_FALSE(world.is_valid(e));
}

TEST(ECSTest, AddComponent) {
    World world;
    Entity e = world.create_entity();
    auto& comp = world.add_component<TestComponent>(e, TestComponent{42});
    EXPECT_EQ(comp.value, 42);
    EXPECT_TRUE(world.has_component<TestComponent>(e));
}

TEST(ECSTest, GetComponent) {
    World world;
    Entity e = world.create_entity();
    world.add_component<TestComponent>(e, TestComponent{99});

    auto* comp = world.get_component<TestComponent>(e);
    ASSERT_NE(comp, nullptr);
    EXPECT_EQ(comp->value, 99);
}

TEST(ECSTest, RemoveComponent) {
    World world;
    Entity e = world.create_entity();
    world.add_component<TestComponent>(e, TestComponent{1});
    EXPECT_TRUE(world.has_component<TestComponent>(e));

    world.remove_component<TestComponent>(e);
    EXPECT_FALSE(world.has_component<TestComponent>(e));
    EXPECT_EQ(world.get_component<TestComponent>(e), nullptr);
}

TEST(ECSTest, MultipleComponents) {
    World world;
    Entity e = world.create_entity();
    world.add_component<TestComponent>(e, TestComponent{10});
    world.add_component<AnotherComponent>(e, AnotherComponent{3.14f});

    EXPECT_TRUE(world.has_component<TestComponent>(e));
    EXPECT_TRUE(world.has_component<AnotherComponent>(e));

    auto* tc = world.get_component<TestComponent>(e);
    auto* ac = world.get_component<AnotherComponent>(e);
    EXPECT_EQ(tc->value, 10);
    EXPECT_FLOAT_EQ(ac->data, 3.14f);
}

TEST(ECSTest, QueryEntities) {
    World world;
    Entity e1 = world.create_entity();
    Entity e2 = world.create_entity();
    Entity e3 = world.create_entity();

    world.add_component<TestComponent>(e1, TestComponent{1});
    world.add_component<TestComponent>(e2, TestComponent{2});
    world.add_component<AnotherComponent>(e2, AnotherComponent{2.0f});
    world.add_component<TestComponent>(e3, TestComponent{3});

    auto results = world.query<TestComponent>();
    EXPECT_EQ(results.size(), 3u);

    auto results2 = world.query<TestComponent, AnotherComponent>();
    EXPECT_EQ(results2.size(), 1u);
    EXPECT_EQ(results2[0], e2);
}

TEST(ECSTest, EntityCount) {
    World world;
    EXPECT_EQ(world.entity_count(), 0u);

    world.create_entity();
    EXPECT_EQ(world.entity_count(), 1u);

    world.create_entity();
    world.create_entity();
    EXPECT_EQ(world.entity_count(), 3u);
}

TEST(ECSTest, GetComponentType) {
    ComponentType t1 = get_component_type<TestComponent>();
    ComponentType t2 = get_component_type<TestComponent>();
    ComponentType t3 = get_component_type<AnotherComponent>();

    EXPECT_EQ(t1, t2);
    EXPECT_NE(t1, t3);
}
