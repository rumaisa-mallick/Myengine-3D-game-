#include "engine/rendering/mesh.h"
#include "engine/core/logger.h"

namespace engine {

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    : m_vertex_count(static_cast<uint32_t>(vertices.size())),
      m_index_count(static_cast<uint32_t>(indices.size())) {
    LOG_DEBUG("Creating mesh: %u vertices, %u indices", m_vertex_count, m_index_count);
    // glGenVertexArrays(1, &m_vao);
    // glGenBuffers(1, &m_vbo);
    // glGenBuffers(1, &m_ebo);
    // ... upload to GPU
}

void Mesh::bind() const {
    // glBindVertexArray(m_vao);
}

void Mesh::unbind() const {
    // glBindVertexArray(0);
}

void Mesh::draw() const {
    bind();
    // glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
    unbind();
}

Mesh Mesh::create_cube() {
    std::vector<Vertex> vertices = {
        // Front face
        {{-0.5f, -0.5f,  0.5f}, { 0,  0,  1}, {0, 0}},
        {{ 0.5f, -0.5f,  0.5f}, { 0,  0,  1}, {1, 0}},
        {{ 0.5f,  0.5f,  0.5f}, { 0,  0,  1}, {1, 1}},
        {{-0.5f,  0.5f,  0.5f}, { 0,  0,  1}, {0, 1}},
        // Back face
        {{ 0.5f, -0.5f, -0.5f}, { 0,  0, -1}, {0, 0}},
        {{-0.5f, -0.5f, -0.5f}, { 0,  0, -1}, {1, 0}},
        {{-0.5f,  0.5f, -0.5f}, { 0,  0, -1}, {1, 1}},
        {{ 0.5f,  0.5f, -0.5f}, { 0,  0, -1}, {0, 1}},
        // Top face
        {{-0.5f,  0.5f,  0.5f}, { 0,  1,  0}, {0, 0}},
        {{ 0.5f,  0.5f,  0.5f}, { 0,  1,  0}, {1, 0}},
        {{ 0.5f,  0.5f, -0.5f}, { 0,  1,  0}, {1, 1}},
        {{-0.5f,  0.5f, -0.5f}, { 0,  1,  0}, {0, 1}},
        // Bottom face
        {{-0.5f, -0.5f, -0.5f}, { 0, -1,  0}, {0, 0}},
        {{ 0.5f, -0.5f, -0.5f}, { 0, -1,  0}, {1, 0}},
        {{ 0.5f, -0.5f,  0.5f}, { 0, -1,  0}, {1, 1}},
        {{-0.5f, -0.5f,  0.5f}, { 0, -1,  0}, {0, 1}},
        // Right face
        {{ 0.5f, -0.5f,  0.5f}, { 1,  0,  0}, {0, 0}},
        {{ 0.5f, -0.5f, -0.5f}, { 1,  0,  0}, {1, 0}},
        {{ 0.5f,  0.5f, -0.5f}, { 1,  0,  0}, {1, 1}},
        {{ 0.5f,  0.5f,  0.5f}, { 1,  0,  0}, {0, 1}},
        // Left face
        {{-0.5f, -0.5f, -0.5f}, {-1,  0,  0}, {0, 0}},
        {{-0.5f, -0.5f,  0.5f}, {-1,  0,  0}, {1, 0}},
        {{-0.5f,  0.5f,  0.5f}, {-1,  0,  0}, {1, 1}},
        {{-0.5f,  0.5f, -0.5f}, {-1,  0,  0}, {0, 1}},
    };

    std::vector<uint32_t> indices;
    for (uint32_t i = 0; i < 6; i++) {
        uint32_t base = i * 4;
        indices.push_back(base);     indices.push_back(base + 1); indices.push_back(base + 2);
        indices.push_back(base);     indices.push_back(base + 2); indices.push_back(base + 3);
    }

    return Mesh(vertices, indices);
}

Mesh Mesh::create_quad() {
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, 0}, {0, 0, 1}, {0, 0}},
        {{ 0.5f, -0.5f, 0}, {0, 0, 1}, {1, 0}},
        {{ 0.5f,  0.5f, 0}, {0, 0, 1}, {1, 1}},
        {{-0.5f,  0.5f, 0}, {0, 0, 1}, {0, 1}},
    };
    std::vector<uint32_t> indices = {0, 1, 2, 0, 2, 3};
    return Mesh(vertices, indices);
}

Mesh Mesh::create_sphere(uint32_t segments) {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for (uint32_t y = 0; y <= segments; y++) {
        for (uint32_t x = 0; x <= segments; x++) {
            float x_seg = static_cast<float>(x) / segments;
            float y_seg = static_cast<float>(y) / segments;
            float x_pos = std::cos(x_seg * 2.0f * PI) * std::sin(y_seg * PI);
            float y_pos = std::cos(y_seg * PI);
            float z_pos = std::sin(x_seg * 2.0f * PI) * std::sin(y_seg * PI);

            vertices.push_back({
                {x_pos * 0.5f, y_pos * 0.5f, z_pos * 0.5f},
                {x_pos, y_pos, z_pos},
                {x_seg, y_seg}
            });
        }
    }

    for (uint32_t y = 0; y < segments; y++) {
        for (uint32_t x = 0; x < segments; x++) {
            uint32_t a = y * (segments + 1) + x;
            uint32_t b = a + segments + 1;
            indices.push_back(a); indices.push_back(b); indices.push_back(a + 1);
            indices.push_back(a + 1); indices.push_back(b); indices.push_back(b + 1);
        }
    }

    return Mesh(vertices, indices);
}

} // namespace engine
