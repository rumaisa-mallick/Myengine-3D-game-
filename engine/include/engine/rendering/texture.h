#pragma once

#include <string>
#include <cstdint>

namespace engine {

enum class TextureFormat {
    RGB,
    RGBA,
    Depth
};

class Texture {
public:
    Texture() = default;
    Texture(uint32_t width, uint32_t height, TextureFormat format, const void* data = nullptr);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void unbind() const;

    uint32_t get_width() const { return m_width; }
    uint32_t get_height() const { return m_height; }
    uint32_t get_id() const { return m_texture_id; }

    static Texture from_file(const std::string& path);
    static Texture create_white();

private:
    uint32_t m_texture_id = 0;
    uint32_t m_width = 0, m_height = 0;
    TextureFormat m_format = TextureFormat::RGBA;
};

} // namespace engine
