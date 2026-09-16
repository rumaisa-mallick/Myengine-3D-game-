#include "editor/editor_camera.h"

namespace editor {

EditorCamera::EditorCamera() {
    update_position();
}

void EditorCamera::update(float dt) {
    // Handle keyboard input for camera movement
    auto& input = engine::Input::instance();
    engine::Vec3 movement;

    if (input.is_key_pressed(engine::KeyCode::W)) movement.z -= 1;
    if (input.is_key_pressed(engine::KeyCode::S)) movement.z += 1;
    if (input.is_key_pressed(engine::KeyCode::A)) movement.x -= 1;
    if (input.is_key_pressed(engine::KeyCode::D)) movement.x += 1;
    if (input.is_key_pressed(engine::KeyCode::Space)) movement.y += 1;
    if (input.is_key_pressed(engine::KeyCode::L)) movement.y -= 1;

    if (movement.length_sq() > 0) {
        movement = movement.normalized() * m_move_speed * dt;
        m_camera.set_position(m_camera.get_position() + movement);
    }
}

void EditorCamera::on_mouse_move(float dx, float dy) {
    m_yaw -= dx * m_look_sensitivity;
    m_pitch -= dy * m_look_sensitivity;
    m_pitch = engine::math::clamp(m_pitch, -89.0f, 89.0f);
    update_position();
}

void EditorCamera::on_scroll(float offset) {
    m_distance -= offset * m_zoom_speed;
    m_distance = engine::math::clamp(m_distance, 1.0f, 100.0f);
    update_position();
}

void EditorCamera::update_position() {
    float pitch_rad = engine::math::to_radians(m_pitch);
    float yaw_rad = engine::math::to_radians(m_yaw);

    engine::Vec3 pos;
    pos.x = m_distance * std::cos(pitch_rad) * std::sin(yaw_rad);
    pos.y = m_distance * std::sin(pitch_rad);
    pos.z = m_distance * std::cos(pitch_rad) * std::cos(yaw_rad);

    m_camera.set_position(pos);
    m_camera.look_at(engine::Vec3::zero());
}

} // namespace editor
