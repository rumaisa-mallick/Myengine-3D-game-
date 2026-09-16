#pragma once

#include "engine/math/math_utils.h"

namespace engine {

class Camera {
public:
    enum class Projection { Perspective, Orthographic };

    Camera();

    void set_position(Vec3 pos) { m_position = pos; }
    void set_target(Vec3 target) { m_target = target; }
    void set_fov(float fov) { m_fov = fov; }
    void set_aspect(float aspect) { m_aspect = aspect; }
    void set_near(float near) { m_near = near; }
    void set_far(float far) { m_far = far; }
    void set_projection(Projection proj) { m_projection = proj; }

    Vec3 get_position() const { return m_position; }
    Vec3 get_forward() const { return (m_target - m_position).normalized(); }
    Vec3 get_right() const { return get_forward().cross(Vec3::up()).normalized(); }

    Mat4 get_view_matrix() const;
    Mat4 get_projection_matrix() const;
    Mat4 get_view_projection() const;

    void look_at(Vec3 target) { m_target = target; }

private:
    Vec3 m_position = Vec3{0, 0, 5};
    Vec3 m_target = Vec3::zero();
    float m_fov = 45.0f;
    float m_aspect = 16.0f / 9.0f;
    float m_near = 0.1f;
    float m_far = 1000.0f;
    Projection m_projection = Projection::Perspective;
};

} // namespace engine
