#include "engine/rendering/texture.h"
#include "engine/core/logger.h"
#include <vector>

namespace engine {

Texture::Texture(uint32_t width, uint32_t height, TextureFormat format, const void* data)
    : m_width(width), m_height(height), m_format(format) {
    LOG_DEBUG("Creating texture: %ux%u", width, height);
    // glGenTextures(1, &m_texture_id);
    // glBindTexture(GL_TEXTURE_2D, m_texture_id);
    // glTexImage2D(...)
}

Texture::~Texture() {
    if (m_texture_id) {
        // glDeleteTextures(1, &m_texture_id);
    }
}

void Texture::bind(uint32_t slot) const {
    // glActiveTexture(GL_TEXTURE0 + slot);
    // glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::unbind() const {
    // glBindTexture(GL_TEXTURE_2D, 0);
}

Texture Texture::from_file(const std::string& path) {
    LOG_DEBUG("Loading texture from file: %s", path.c_str());
    // stb_image loading would go here
    return Texture{};
}

Texture Texture::create_white() {
    uint32_t white = 0xFFFFFFFF;
    return Texture(1, 1, TextureFormat::RGBA, &white);
}

} // namespace engine
