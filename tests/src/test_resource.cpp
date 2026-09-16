#include <gtest/gtest.h>
#include "engine/resource/resource_manager.h"
#include "engine/resource/asset_loader.h"

using namespace engine;

TEST(ResourceManagerTest, Singleton) {
    auto& rm1 = ResourceManager::instance();
    auto& rm2 = ResourceManager::instance();
    EXPECT_EQ(&rm1, &rm2);
}

TEST(ResourceManagerTest, ResourceCount) {
    auto& rm = ResourceManager::instance();
    rm.clear();
    EXPECT_EQ(rm.resource_count(), 0u);
}

TEST(ResourceManagerTest, Unload) {
    auto& rm = ResourceManager::instance();
    rm.clear();
    rm.unload("nonexistent");
    EXPECT_EQ(rm.resource_count(), 0u);
}

TEST(AssetLoaderTest, GetExtension) {
    EXPECT_EQ(AssetLoader::get_extension("file.txt"), ".txt");
    EXPECT_EQ(AssetLoader::get_extension("path/to/image.png"), ".png");
    EXPECT_EQ(AssetLoader::get_extension("noext"), "");
}

TEST(AssetLoaderTest, GetDirectory) {
    EXPECT_EQ(AssetLoader::get_directory("/path/to/file.txt"), "/path/to");
    EXPECT_EQ(AssetLoader::get_directory("file.txt"), ".");
}

TEST(AssetLoaderTest, GetFilename) {
    EXPECT_EQ(AssetLoader::get_filename("/path/to/file.txt"), "file.txt");
    EXPECT_EQ(AssetLoader::get_filename("file.txt"), "file.txt");
}
