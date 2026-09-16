#pragma once

#include <array>
#include <functional>

namespace engine {

enum class KeyCode {
    Unknown = 0,
    Space, Escape, Enter, Tab, Backspace,
    Up, Down, Left, Right,
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    Count
};

enum class MouseButton {
    Left = 0, Right, Middle, Count
};

class Input {
public:
    static Input& instance();

    bool is_key_pressed(KeyCode key) const;
    bool is_key_just_pressed(KeyCode key) const;
    bool is_mouse_button_pressed(MouseButton button) const;

    void get_mouse_position(double& x, double& y) const;
    void get_mouse_delta(double& dx, double& dy) const;

    void update();

private:
    Input() = default;

    std::array<bool, static_cast<size_t>(KeyCode::Count)> m_keys{};
    std::array<bool, static_cast<size_t>(KeyCode::Count)> m_prev_keys{};
    std::array<bool, static_cast<size_t>(MouseButton::Count)> m_mouse_buttons{};
    double m_mouse_x = 0.0, m_mouse_y = 0.0;
    double m_last_mouse_x = 0.0, m_last_mouse_y = 0.0;
    double m_mouse_dx = 0.0, m_mouse_dy = 0.0;
};

} // namespace engine
