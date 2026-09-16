#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <any>

namespace engine {

class ResourceManager {
public:
    static ResourceManager& instance();

    template<typename T>
    std::shared_ptr<T> load(const std::string& path) {
        auto it = m_resources.find(path);
        if (it != m_resources.end()) {
            return std::any_cast<std::shared_ptr<T>>(it->second);
        }

        auto loader = m_loaders.find(typeid(T).hash_code());
        if (loader != m_loaders.end()) {
            auto resource = std::any_cast<std::function<std::shared_ptr<T>(const std::string&)>>(loader->second)(path);
            m_resources[path] = resource;
            return resource;
        }

        return nullptr;
    }

    template<typename T>
    void register_loader(std::function<std::shared_ptr<T>(const std::string&)> loader) {
        m_loaders[typeid(T).hash_code()] = loader;
    }

    void unload(const std::string& path);
    void clear();
    size_t resource_count() const { return m_resources.size(); }

private:
    ResourceManager() = default;
    std::unordered_map<std::string, std::any> m_resources;
    std::unordered_map<size_t, std::any> m_loaders;
};

} // namespace engine
