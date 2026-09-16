#pragma once

#include "engine/engine.h"
#include <string>

namespace editor {

class EditorApp : public engine::Application {
public:
    EditorApp();
    ~EditorApp() override;

protected:
    void on_init() override;
    void on_update(float dt) override;
    void on_render() override;
    void on_shutdown() override;

private:
    engine::Renderer m_renderer;
    engine::Camera m_editor_camera;
    std::shared_ptr<engine::Scene> m_active_scene;
};

} // namespace editor
