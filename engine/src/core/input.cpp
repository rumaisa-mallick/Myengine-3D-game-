#include "engine/core/input.h"

namespace engine {

Input& Input::instance() {
    static Input s_instance;
    return s_instance;
}

bool Input::is_key_pressed(KeyCode key) const {
    auto idx = static_cast<size_t>(key);
    return idx < m_keys.size() && m_keys[idx];
}

bool Input::is_key_just_pressed(KeyCode key) const {
    auto idx = static_cast<size_t>(key);
    return idx < m_keys.size() && m_keys[idx] && !m_prev_keys[idx];
}

bool Input::is_mouse_button_pressed(MouseButton button) const {
    auto idx = static_cast<size_t>(button);
    return idx < m_mouse_buttons.size() && m_mouse_buttons[idx];
}

void Input::get_mouse_position(double& x, double& y) const {
    x = m_mouse_x;
    y = m_mouse_y;
}

void Input::get_mouse_delta(double& dx, double& dy) const {
    dx = m_mouse_dx;
    dy = m_mouse_dy;
}

void Input::update() {
    m_prev_keys = m_keys;
    m_mouse_dx = m_mouse_x - m_last_mouse_x;
    m_mouse_dy = m_mouse_y - m_last_mouse_y;
    m_last_mouse_x = m_mouse_x;
    m_last_mouse_y = m_mouse_y;
}

} // namespace engine
