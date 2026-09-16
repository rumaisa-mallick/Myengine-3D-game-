#include <gtest/gtest.h>
#include "engine/scene/scene.h"
#include "engine/scene/scene_manager.h"

using namespace engine;

TEST(SceneTest, Creation) {
    Scene scene("TestScene");
    EXPECT_EQ(scene.get_name(), "TestScene");
}

TEST(SceneTest, SetName) {
    Scene scene("Old");
    scene.set_name("New");
    EXPECT_EQ(scene.get_name(), "New");
}

TEST(SceneTest, GetWorld) {
    Scene scene("Test");
    World& world = scene.get_world();
    Entity e = world.create_entity();
    EXPECT_NE(e, NULL_ENTITY);
}

TEST(SceneTest, OnEnterExit) {
    Scene scene("Test");
    scene.on_enter();
    scene.on_exit();
    // Should not crash
}

TEST(SceneManagerTest, CreateScene) {
    auto& sm = SceneManager::instance();
    auto scene = sm.create_scene("SMTest");
    EXPECT_NE(scene, nullptr);
    EXPECT_EQ(scene->get_name(), "SMTest");
}

TEST(SceneManagerTest, LoadScene) {
    auto& sm = SceneManager::instance();
    sm.create_scene("LoadTest");
    sm.load_scene("LoadTest");
    auto current = sm.get_current_scene();
    EXPECT_NE(current, nullptr);
    EXPECT_EQ(current->get_name(), "LoadTest");
}

TEST(SceneManagerTest, GetScene) {
    auto& sm = SceneManager::instance();
    sm.create_scene("GetTest");
    auto scene = sm.get_scene("GetTest");
    EXPECT_NE(scene, nullptr);

    auto missing = sm.get_scene("NonExistent");
    EXPECT_EQ(missing, nullptr);
}

TEST(SceneManagerTest, UnloadScene) {
    auto& sm = SceneManager::instance();
    sm.create_scene("UnloadTest");
    sm.load_scene("UnloadTest");
    sm.unload_scene("UnloadTest");
    auto scene = sm.get_scene("UnloadTest");
    EXPECT_EQ(scene, nullptr);
}
