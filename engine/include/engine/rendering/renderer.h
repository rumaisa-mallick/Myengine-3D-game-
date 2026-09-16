#pragma once

#include "engine/rendering/shader.h"
#include "engine/rendering/mesh.h"
#include "engine/rendering/texture.h"
#include "engine/rendering/camera.h"
#include "engine/math/math_utils.h"
#include <vector>
#include <memory>

namespace engine {

struct RenderCommand {
    const Mesh* mesh = nullptr;
    const Shader* shader = nullptr;
    const Texture* texture = nullptr;
    Mat4 transform;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void begin_frame();
    void submit(const RenderCommand& command);
    void end_frame();

    void set_clear_color(float r, float g, float b, float a = 1.0f);
    void set_viewport(int x, int y, int width, int height);

    void init();
    void shutdown();

private:
    std::vector<RenderCommand> m_command_queue;
    float m_clear_r = 0.1f, m_clear_g = 0.1f, m_clear_b = 0.1f, m_clear_a = 1.0f;
    bool m_initialized = false;
};

} // namespace engine
