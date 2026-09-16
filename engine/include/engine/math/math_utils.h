#pragma once

#include <cmath>
#include <algorithm>

namespace engine {

constexpr float PI = 3.14159265358979323846f;
constexpr float DEG_TO_RAD = PI / 180.0f;
constexpr float RAD_TO_DEG = 180.0f / PI;
constexpr float EPSILON = 1e-6f;

struct Vec2 {
    float x = 0.0f, y = 0.0f;

    Vec2() = default;
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    Vec2 operator/(float s) const { return {x / s, y / s}; }
    Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
    Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
    Vec2& operator*=(float s) { x *= s; y *= s; return *this; }
    bool operator==(const Vec2& v) const { return std::abs(x - v.x) < EPSILON && std::abs(y - v.y) < EPSILON; }
    bool operator!=(const Vec2& v) const { return !(*this == v); }

    float length() const { return std::sqrt(x * x + y * y); }
    float length_sq() const { return x * x + y * y; }
    Vec2 normalized() const { float l = length(); return l > EPSILON ? *this / l : Vec2{}; }
    float dot(const Vec2& v) const { return x * v.x + y * v.y; }

    static Vec2 zero() { return {0, 0}; }
    static Vec2 one() { return {1, 1}; }
    static Vec2 up() { return {0, 1}; }
    static Vec2 right() { return {1, 0}; }
};

struct Vec3 {
    float x = 0.0f, y = 0.0f, z = 0.0f;

    Vec3() = default;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(Vec2 v, float z) : x(v.x), y(v.y), z(z) {}

    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3 operator-(const Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }
    Vec3 operator/(float s) const { return {x / s, y / s, z / s}; }
    Vec3& operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vec3& operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vec3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    Vec3 operator-() const { return {-x, -y, -z}; }
    bool operator==(const Vec3& v) const { return std::abs(x - v.x) < EPSILON && std::abs(y - v.y) < EPSILON && std::abs(z - v.z) < EPSILON; }

    float length() const { return std::sqrt(x * x + y * y + z * z); }
    float length_sq() const { return x * x + y * y + z * z; }
    Vec3 normalized() const { float l = length(); return l > EPSILON ? *this / l : Vec3{}; }
    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 cross(const Vec3& v) const { return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x}; }

    Vec2 xy() const { return {x, y}; }

    static Vec3 zero() { return {0, 0, 0}; }
    static Vec3 one() { return {1, 1, 1}; }
    static Vec3 up() { return {0, 1, 0}; }
    static Vec3 right() { return {1, 0, 0}; }
    static Vec3 forward() { return {0, 0, -1}; }
};

struct Vec4 {
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

    Vec4() = default;
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(Vec3 v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

    Vec3 xyz() const { return {x, y, z}; }

    Vec4 operator+(const Vec4& v) const { return {x + v.x, y + v.y, z + v.z, w + v.w}; }
    Vec4 operator*(float s) const { return {x * s, y * s, z * s, w * s}; }
};

struct Mat4 {
    float data[16] = {};

    Mat4() {
        data[0] = data[5] = data[10] = data[15] = 1.0f;
    }

    float& at(int row, int col) { return data[col * 4 + row]; }
    const float& at(int row, int col) const { return data[col * 4 + row]; }
    const float* ptr() const { return data; }

    Mat4 operator*(const Mat4& m) const {
        Mat4 result;
        std::fill(result.data, result.data + 16, 0.0f);
        for (int c = 0; c < 4; c++)
            for (int r = 0; r < 4; r++)
                for (int k = 0; k < 4; k++)
                    result.at(r, c) += at(r, k) * m.at(k, c);
        return result;
    }

    Vec4 operator*(const Vec4& v) const {
        return {
            at(0,0)*v.x + at(0,1)*v.y + at(0,2)*v.z + at(0,3)*v.w,
            at(1,0)*v.x + at(1,1)*v.y + at(1,2)*v.z + at(1,3)*v.w,
            at(2,0)*v.x + at(2,1)*v.y + at(2,2)*v.z + at(2,3)*v.w,
            at(3,0)*v.x + at(3,1)*v.y + at(3,2)*v.z + at(3,3)*v.w
        };
    }

    static Mat4 identity();
    static Mat4 translate(Vec3 v);
    static Mat4 scale(Vec3 v);
    static Mat4 rotate_x(float angle);
    static Mat4 rotate_y(float angle);
    static Mat4 rotate_z(float angle);
    static Mat4 perspective(float fov, float aspect, float near, float far);
    static Mat4 look_at(Vec3 eye, Vec3 target, Vec3 up);
};

struct Quaternion {
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;

    Quaternion() = default;
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Quaternion operator*(const Quaternion& q) const {
        return {
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w,
            w*q.w - x*q.x - y*q.y - z*q.z
        };
    }

    Quaternion normalized() const {
        float len = std::sqrt(x*x + y*y + z*z + w*w);
        return {x/len, y/len, z/len, w/len};
    }

    Quaternion conjugate() const { return {-x, -y, -z, w}; }

    Vec3 rotate_vec3(Vec3 v) const {
        Quaternion qv(v.x, v.y, v.z, 0);
        Quaternion result = (*this) * qv * conjugate();
        return {result.x, result.y, result.z};
    }

    Mat4 to_mat4() const;

    static Quaternion from_axis_angle(Vec3 axis, float angle);
    static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
};

namespace math {

inline float to_radians(float degrees) { return degrees * DEG_TO_RAD; }
inline float to_degrees(float radians) { return radians * RAD_TO_DEG; }
inline float clamp(float value, float min, float max) { return std::max(min, std::min(max, value)); }
inline float lerp(float a, float b, float t) { return a + (b - a) * t; }
inline Vec2 lerp(Vec2 a, Vec2 b, float t) { return a + (b - a) * t; }
inline Vec3 lerp(Vec3 a, Vec3 b, float t) { return a + (b - a) * t; }

} // namespace math
} // namespace engine
