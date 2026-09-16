#include "editor/editor_app.h"
#include "editor/editor_ui.h"
#include "editor/editor_camera.h"
#include "editor/scene_hierarchy.h"
#include "editor/inspector.h"
#include "editor/content_browser.h"

namespace editor {

EditorApp::EditorApp() : engine::Application(engine::AppConfig{"MyEngine Editor", 1920, 1080}) {
}

EditorApp::~EditorApp() = default;

void EditorApp::on_init() {
    m_renderer.init();

    m_active_scene = engine::SceneManager::instance().create_scene("Default Scene");
    engine::SceneManager::instance().load_scene("Default Scene");

    auto& world = m_active_scene->get_world();
    auto entity = world.create_entity();
    world.add_component<engine::TagComponent>(entity, engine::TagComponent{"Main Camera"});
    world.add_component<engine::TransformComponent>(entity, engine::TransformComponent{{0, 2, 5}});

    LOG_INFO("Editor initialized");
}

void EditorApp::on_update(float dt) {
    engine::SceneManager::instance().update(dt);
}

void EditorApp::on_render() {
    m_renderer.begin_frame();
    m_renderer.end_frame();
}

void EditorApp::on_shutdown() {
    m_renderer.shutdown();
    LOG_INFO("Editor shut down");
}

} // namespace editor

int main() {
    editor::EditorApp app;
    app.run();
    return 0;
}
