#pragma once

#include <string>
#include <memory>

namespace engine {

struct AppConfig {
    std::string name = "MyEngine Application";
    uint32_t window_width = 1280;
    uint32_t window_height = 720;
    bool vsync = true;
};

class Application {
public:
    Application(const AppConfig& config = AppConfig());
    virtual ~Application();

    void run();
    void quit();

    static Application& instance();

protected:
    virtual void on_init() {}
    virtual void on_update(float dt) {}
    virtual void on_render() {}
    virtual void on_shutdown() {}

private:
    bool m_running = false;
    AppConfig m_config;
    static Application* s_instance;
};

} // namespace engine
