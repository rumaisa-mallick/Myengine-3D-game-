#include "engine/rendering/renderer.h"
#include "engine/core/logger.h"

namespace engine {

Renderer::Renderer() {
    LOG_INFO("Renderer created");
}

Renderer::~Renderer() {
    shutdown();
}

void Renderer::init() {
    if (m_initialized) return;
    LOG_INFO("Renderer initialized");
    m_initialized = true;
}

void Renderer::shutdown() {
    if (!m_initialized) return;
    m_command_queue.clear();
    m_initialized = false;
    LOG_INFO("Renderer shut down");
}

void Renderer::begin_frame() {
    m_command_queue.clear();
}

void Renderer::submit(const RenderCommand& command) {
    m_command_queue.push_back(command);
}

void Renderer::end_frame() {
    for (const auto& cmd : m_command_queue) {
        if (cmd.shader) cmd.shader->bind();
        if (cmd.texture) cmd.texture->bind();
        if (cmd.mesh) cmd.mesh->draw();
    }
}

void Renderer::set_clear_color(float r, float g, float b, float a) {
    m_clear_r = r;
    m_clear_g = g;
    m_clear_b = b;
    m_clear_a = a;
}

void Renderer::set_viewport(int x, int y, int width, int height) {
    // Platform-specific viewport call
}

} // namespace engine
