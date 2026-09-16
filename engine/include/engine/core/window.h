#pragma once

#include <string>
#include <functional>

namespace engine {

struct WindowProps {
    std::string title;
    uint32_t width;
    uint32_t height;

    WindowProps(const std::string& t = "MyEngine",
                uint32_t w = 1280,
                uint32_t h = 720)
        : title(t), width(w), height(h) {}
};

class Window {
public:
    Window(const WindowProps& props = WindowProps());
    ~Window();

    void poll_events();
    bool should_close() const;
    void swap_buffers();

    uint32_t get_width() const { return m_width; }
    uint32_t get_height() const { return m_height; }
    void* get_native_window() const { return m_native_window; }

    void set_title(const std::string& title);
    void set_size(uint32_t width, uint32_t height);

private:
    uint32_t m_width;
    uint32_t m_height;
    std::string m_title;
    void* m_native_window = nullptr;
};

} // namespace engine
