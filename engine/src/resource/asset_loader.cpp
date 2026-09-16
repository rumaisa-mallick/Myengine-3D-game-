#include "engine/resource/asset_loader.h"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace engine {

std::vector<char> AssetLoader::read_file(const std::string& path) {
    std::ifstream file(path, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        return {};
    }

    size_t size = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(size);
    file.seekg(0);
    file.read(buffer.data(), size);
    return buffer;
}

std::string AssetLoader::read_text(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

bool AssetLoader::file_exists(const std::string& path) {
    return std::filesystem::exists(path);
}

std::string AssetLoader::get_extension(const std::string& path) {
    auto pos = path.rfind('.');
    return pos != std::string::npos ? path.substr(pos) : "";
}

std::string AssetLoader::get_directory(const std::string& path) {
    auto pos = path.find_last_of("/\\");
    return pos != std::string::npos ? path.substr(0, pos) : ".";
}

std::string AssetLoader::get_filename(const std::string& path) {
    auto pos = path.find_last_of("/\\");
    return pos != std::string::npos ? path.substr(pos + 1) : path;
}

} // namespace engine
