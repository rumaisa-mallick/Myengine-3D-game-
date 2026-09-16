#include "engine/rendering/camera.h"

namespace engine {

Camera::Camera() = default;

Mat4 Camera::get_view_matrix() const {
    return Mat4::look_at(m_position, m_target, Vec3::up());
}

Mat4 Camera::get_projection_matrix() const {
    if (m_projection == Projection::Perspective) {
        float fov_rad = m_fov * DEG_TO_RAD;
        return Mat4::perspective(fov_rad, m_aspect, m_near, m_far);
    } else {
        float ortho_size = 5.0f;
        float left = -ortho_size * m_aspect;
        float right = ortho_size * m_aspect;
        float bottom = -ortho_size;
        float top = ortho_size;

        Mat4 m;
        std::fill(m.data, m.data + 16, 0.0f);
        m.at(0, 0) = 2.0f / (right - left);
        m.at(1, 1) = 2.0f / (top - bottom);
        m.at(2, 2) = -1.0f; // Simplified for 2D
        m.at(0, 3) = -(right + left) / (right - left);
        m.at(1, 3) = -(top + bottom) / (top - bottom);
        return m;
    }
}

Mat4 Camera::get_view_projection() const {
    return get_projection_matrix() * get_view_matrix();
}

} // namespace engine
