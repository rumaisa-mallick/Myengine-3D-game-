#include "engine/core/window.h"
#include "engine/core/logger.h"

namespace engine {

Window::Window(const WindowProps& props)
    : m_width(props.width), m_height(props.height), m_title(props.title) {
    LOG_INFO("Creating window: %s (%ux%u)", m_title.c_str(), m_width, m_height);
    // Platform-specific window creation would go here
    // For now, this is a stub
}

Window::~Window() {
    LOG_INFO("Destroying window");
}

void Window::poll_events() {
    // Platform-specific event polling
}

bool Window::should_close() const {
    return false; // Stub
}

void Window::swap_buffers() {
    // Platform-specific buffer swap
}

void Window::set_title(const std::string& title) {
    m_title = title;
}

void Window::set_size(uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
}

} // namespace engine
