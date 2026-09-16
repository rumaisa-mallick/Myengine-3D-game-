#include "engine/core/application.h"
#include "engine/core/window.h"
#include "engine/core/input.h"
#include "engine/core/timer.h"
#include "engine/core/logger.h"
#include <memory>

namespace engine {

Application* Application::s_instance = nullptr;

Application::Application(const AppConfig& config)
    : m_config(config) {
    s_instance = this;
    LOG_INFO("Application created: %s", config.name.c_str());
}

Application::~Application() {
    LOG_INFO("Application destroyed");
    s_instance = nullptr;
}

Application& Application::instance() {
    assert(s_instance && "Application not created!");
    return *s_instance;
}

void Application::run() {
    LOG_INFO("Starting application run loop");

    auto window = std::make_unique<Window>(WindowProps{m_config.name, m_config.window_width, m_config.window_height});
    Timer timer;

    m_running = true;
    on_init();

    while (m_running && !window->should_close()) {
        timer.update();
        window->poll_events();
        Input::instance().update();

        float dt = timer.delta_time();
        on_update(dt);
        on_render();

        window->swap_buffers();
    }

    on_shutdown();
    m_running = false;
    LOG_INFO("Application run loop ended");
}

void Application::quit() {
    m_running = false;
}

} // namespace engine
