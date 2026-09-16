#pragma once

#include "engine/engine.h"

namespace editor {

class EditorCamera {
public:
    EditorCamera();

    void update(float dt);
    void on_mouse_move(float dx, float dy);
    void on_scroll(float offset);

    engine::Camera& get_camera() { return m_camera; }
    const engine::Camera& get_camera() const { return m_camera; }

private:
    engine::Camera m_camera;
    float m_distance = 10.0f;
    float m_pitch = 30.0f;
    float m_yaw = 0.0f;
    float m_move_speed = 5.0f;
    float m_look_sensitivity = 0.3f;
    float m_zoom_speed = 2.0f;

    void update_position();
};

} // namespace editor
