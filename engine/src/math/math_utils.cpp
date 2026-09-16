#include "engine/math/math_utils.h"
#include <cmath>

namespace engine {

Mat4 Mat4::identity() {
    return Mat4{};
}

Mat4 Mat4::translate(Vec3 v) {
    Mat4 m;
    m.at(0, 3) = v.x;
    m.at(1, 3) = v.y;
    m.at(2, 3) = v.z;
    return m;
}

Mat4 Mat4::scale(Vec3 v) {
    Mat4 m;
    m.at(0, 0) = v.x;
    m.at(1, 1) = v.y;
    m.at(2, 2) = v.z;
    return m;
}

Mat4 Mat4::rotate_x(float angle) {
    float c = std::cos(angle), s = std::sin(angle);
    Mat4 m;
    m.at(1, 1) = c;  m.at(1, 2) = -s;
    m.at(2, 1) = s;  m.at(2, 2) = c;
    return m;
}

Mat4 Mat4::rotate_y(float angle) {
    float c = std::cos(angle), s = std::sin(angle);
    Mat4 m;
    m.at(0, 0) = c;  m.at(0, 2) = s;
    m.at(2, 0) = -s; m.at(2, 2) = c;
    return m;
}

Mat4 Mat4::rotate_z(float angle) {
    float c = std::cos(angle), s = std::sin(angle);
    Mat4 m;
    m.at(0, 0) = c;  m.at(0, 1) = -s;
    m.at(1, 0) = s;  m.at(1, 1) = c;
    return m;
}

Mat4 Mat4::perspective(float fov, float aspect, float near_plane, float far_plane) {
    float tan_half = std::tan(fov / 2.0f);
    Mat4 m;
    std::fill(m.data, m.data + 16, 0.0f);
    m.at(0, 0) = 1.0f / (aspect * tan_half);
    m.at(1, 1) = 1.0f / tan_half;
    m.at(2, 2) = -(far_plane + near_plane) / (far_plane - near_plane);
    m.at(2, 3) = -(2.0f * far_plane * near_plane) / (far_plane - near_plane);
    m.at(3, 2) = -1.0f;
    return m;
}

Mat4 Mat4::look_at(Vec3 eye, Vec3 target, Vec3 up) {
    Vec3 f = (target - eye).normalized();
    Vec3 r = f.cross(up).normalized();
    Vec3 u = r.cross(f);

    Mat4 m;
    m.at(0, 0) = r.x;  m.at(0, 1) = r.y;  m.at(0, 2) = r.z;  m.at(0, 3) = -r.dot(eye);
    m.at(1, 0) = u.x;  m.at(1, 1) = u.y;  m.at(1, 2) = u.z;  m.at(1, 3) = -u.dot(eye);
    m.at(2, 0) = -f.x; m.at(2, 1) = -f.y; m.at(2, 2) = -f.z; m.at(2, 3) = f.dot(eye);
    m.at(3, 0) = 0;    m.at(3, 1) = 0;    m.at(3, 2) = 0;    m.at(3, 3) = 1;
    return m;
}

Mat4 Quaternion::to_mat4() const {
    float xx = x*x, yy = y*y, zz = z*z;
    float xy = x*y, xz = x*z, yz = y*z;
    float wx = w*x, wy = w*y, wz = w*z;

    Mat4 m;
    m.at(0, 0) = 1 - 2*(yy + zz); m.at(0, 1) = 2*(xy - wz);     m.at(0, 2) = 2*(xz + wy);
    m.at(1, 0) = 2*(xy + wz);     m.at(1, 1) = 1 - 2*(xx + zz); m.at(1, 2) = 2*(yz - wx);
    m.at(2, 0) = 2*(xz - wy);     m.at(2, 1) = 2*(yz + wx);     m.at(2, 2) = 1 - 2*(xx + yy);
    return m;
}

Quaternion Quaternion::from_axis_angle(Vec3 axis, float angle) {
    float half = angle / 2.0f;
    float s = std::sin(half);
    Vec3 n = axis.normalized();
    return {n.x * s, n.y * s, n.z * s, std::cos(half)};
}

Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t) {
    float dot = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
    Quaternion end = b;
    if (dot < 0) {
        end = {-b.x, -b.y, -b.z, -b.w};
        dot = -dot;
    }
    if (dot > 0.9995f) {
        return Quaternion{
            a.x + t*(end.x - a.x), a.y + t*(end.y - a.y),
            a.z + t*(end.z - a.z), a.w + t*(end.w - a.w)
        }.normalized();
    }
    float theta0 = std::acos(dot);
    float theta = theta0 * t;
    float sin_theta = std::sin(theta);
    float sin_theta0 = std::sin(theta0);
    float s0 = std::cos(theta) - dot * sin_theta / sin_theta0;
    float s1 = sin_theta / sin_theta0;
    return {
        s0*a.x + s1*end.x, s0*a.y + s1*end.y,
        s0*a.z + s1*end.z, s0*a.w + s1*end.w
    };
}

} // namespace engine
