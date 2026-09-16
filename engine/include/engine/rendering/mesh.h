#pragma once

#include "engine/math/math_utils.h"
#include <string>
#include <vector>
#include <cstdint>

namespace engine {

struct Vertex {
    Vec3 position;
    Vec3 normal;
    Vec2 tex_coords;
};

class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    void bind() const;
    void unbind() const;
    void draw() const;

    uint32_t get_vertex_count() const { return m_vertex_count; }
    uint32_t get_index_count() const { return m_index_count; }

    static Mesh create_cube();
    static Mesh create_quad();
    static Mesh create_sphere(uint32_t segments = 32);

private:
    uint32_t m_vao = 0, m_vbo = 0, m_ebo = 0;
    uint32_t m_vertex_count = 0;
    uint32_t m_index_count = 0;
};

} // namespace engine
