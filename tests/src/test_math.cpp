#include <gtest/gtest.h>
#include "engine/math/math_utils.h"

using namespace engine;

TEST(Vec2Test, Addition) {
    Vec2 a(1, 2), b(3, 4);
    Vec2 c = a + b;
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 6.0f);
}

TEST(Vec2Test, Subtraction) {
    Vec2 a(5, 7), b(2, 3);
    Vec2 c = a - b;
    EXPECT_FLOAT_EQ(c.x, 3.0f);
    EXPECT_FLOAT_EQ(c.y, 4.0f);
}

TEST(Vec2Test, ScalarMultiplication) {
    Vec2 a(2, 3);
    Vec2 c = a * 3.0f;
    EXPECT_FLOAT_EQ(c.x, 6.0f);
    EXPECT_FLOAT_EQ(c.y, 9.0f);
}

TEST(Vec2Test, Length) {
    Vec2 a(3, 4);
    EXPECT_FLOAT_EQ(a.length(), 5.0f);
}

TEST(Vec2Test, Normalize) {
    Vec2 a(3, 4);
    Vec2 n = a.normalized();
    EXPECT_FLOAT_EQ(n.length(), 1.0f);
}

TEST(Vec2Test, DotProduct) {
    Vec2 a(1, 0), b(0, 1);
    EXPECT_FLOAT_EQ(a.dot(b), 0.0f);
}

TEST(Vec3Test, Addition) {
    Vec3 a(1, 2, 3), b(4, 5, 6);
    Vec3 c = a + b;
    EXPECT_FLOAT_EQ(c.x, 5.0f);
    EXPECT_FLOAT_EQ(c.y, 7.0f);
    EXPECT_FLOAT_EQ(c.z, 9.0f);
}

TEST(Vec3Test, CrossProduct) {
    Vec3 a(1, 0, 0), b(0, 1, 0);
    Vec3 c = a.cross(b);
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 1.0f);
}

TEST(Vec3Test, Length) {
    Vec3 a(1, 2, 2);
    EXPECT_FLOAT_EQ(a.length(), 3.0f);
}

TEST(Vec3Test, DotProduct) {
    Vec3 a(1, 2, 3), b(4, 5, 6);
    EXPECT_FLOAT_EQ(a.dot(b), 32.0f);
}

TEST(Mat4Test, Identity) {
    Mat4 m = Mat4::identity();
    EXPECT_FLOAT_EQ(m.at(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(m.at(1, 1), 1.0f);
    EXPECT_FLOAT_EQ(m.at(2, 2), 1.0f);
    EXPECT_FLOAT_EQ(m.at(3, 3), 1.0f);
    EXPECT_FLOAT_EQ(m.at(0, 1), 0.0f);
}

TEST(Mat4Test, Translation) {
    Mat4 m = Mat4::translate({1, 2, 3});
    EXPECT_FLOAT_EQ(m.at(0, 3), 1.0f);
    EXPECT_FLOAT_EQ(m.at(1, 3), 2.0f);
    EXPECT_FLOAT_EQ(m.at(2, 3), 3.0f);
}

TEST(Mat4Test, Multiplication) {
    Mat4 a = Mat4::translate({1, 0, 0});
    Mat4 b = Mat4::translate({0, 2, 0});
    Mat4 c = a * b;
    EXPECT_FLOAT_EQ(c.at(0, 3), 1.0f);
    EXPECT_FLOAT_EQ(c.at(1, 3), 2.0f);
}

TEST(QuaternionTest, AxisAngle) {
    Vec3 axis(0, 1, 0);
    float angle = PI / 2.0f;
    Quaternion q = Quaternion::from_axis_angle(axis, angle);
    EXPECT_NEAR(q.w, std::cos(angle / 2.0f), EPSILON);
}

TEST(QuaternionTest, RotateVec3) {
    Quaternion q = Quaternion::from_axis_angle({0, 1, 0}, PI / 2.0f);
    Vec3 v = q.rotate_vec3({1, 0, 0});
    EXPECT_NEAR(v.x, 0.0f, EPSILON);
    EXPECT_NEAR(v.z, -1.0f, EPSILON);
}

TEST(MathUtils, ToRadians) {
    EXPECT_FLOAT_EQ(math::to_radians(180.0f), PI);
}

TEST(MathUtils, ToDegrees) {
    EXPECT_FLOAT_EQ(math::to_degrees(PI), 180.0f);
}

TEST(MathUtils, Clamp) {
    EXPECT_FLOAT_EQ(math::clamp(5.0f, 0.0f, 10.0f), 5.0f);
    EXPECT_FLOAT_EQ(math::clamp(-1.0f, 0.0f, 10.0f), 0.0f);
    EXPECT_FLOAT_EQ(math::clamp(15.0f, 0.0f, 10.0f), 10.0f);
}

TEST(MathUtils, Lerp) {
    EXPECT_FLOAT_EQ(math::lerp(0.0f, 10.0f, 0.5f), 5.0f);
    EXPECT_FLOAT_EQ(math::lerp(0.0f, 10.0f, 0.0f), 0.0f);
    EXPECT_FLOAT_EQ(math::lerp(0.0f, 10.0f, 1.0f), 10.0f);
}
