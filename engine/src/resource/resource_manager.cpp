#include "engine/resource/resource_manager.h"

namespace engine {

ResourceManager& ResourceManager::instance() {
    static ResourceManager s_instance;
    return s_instance;
}

void ResourceManager::unload(const std::string& path) {
    m_resources.erase(path);
}

void ResourceManager::clear() {
    m_resources.clear();
}

} // namespace engine
