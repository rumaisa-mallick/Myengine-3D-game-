#pragma once

#include <string>
#include <vector>
#include <functional>

namespace engine {

class AssetLoader {
public:
    static std::vector<char> read_file(const std::string& path);
    static std::string read_text(const std::string& path);
    static bool file_exists(const std::string& path);
    static std::string get_extension(const std::string& path);
    static std::string get_directory(const std::string& path);
    static std::string get_filename(const std::string& path);
};

} // namespace engine
