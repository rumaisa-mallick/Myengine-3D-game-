#include "engine/rendering/shader.h"
#include "engine/core/logger.h"
#include "engine/resource/asset_loader.h"
#include <fstream>
#include <sstream>

namespace engine {

Shader::Shader(const std::string& vertex_src, const std::string& fragment_src) {
    LOG_DEBUG("Creating shader program");
    // Actual OpenGL shader compilation would go here
    // This is a stub for the engine framework
}

Shader::~Shader() {
    if (m_program_id) {
        // glDeleteProgram(m_program_id);
    }
}

void Shader::bind() const {
    // glUseProgram(m_program_id);
}

void Shader::unbind() const {
    // glUseProgram(0);
}

void Shader::set_int(const std::string& name, int value) {
    // glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) {
    // glUniform1f(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::set_vec3(const std::string& name, float x, float y, float z) {
    // glUniform3f(glGetUniformLocation(m_program_id, name.c_str()), x, y, z);
}

void Shader::set_mat4(const std::string& name, const float* data) {
    // glUniformMatrix4fv(glGetUniformLocation(m_program_id, name.c_str()), 1, GL_FALSE, data);
}

Shader Shader::from_files(const std::string& vertex_path, const std::string& fragment_path) {
    std::string vertex_src = AssetLoader::read_text(vertex_path);
    std::string fragment_src = AssetLoader::read_text(fragment_path);
    return Shader(vertex_src, fragment_src);
}

Shader Shader::create_default() {
    std::string vertex_src = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
void main() {
    FragPos = vec3(uModel * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(uModel))) * aNormal;
    TexCoord = aTexCoord;
    gl_Position = uProjection * uView * vec4(FragPos, 1.0);
}
)";

    std::string fragment_src = R"(
#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
uniform vec3 uColor;
uniform vec3 uLightDir;
void main() {
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, normalize(uLightDir)), 0.0);
    vec3 color = uColor * (0.3 + 0.7 * diff);
    FragColor = vec4(color, 1.0);
}
)";

    return Shader(vertex_src, fragment_src);
}

uint32_t Shader::compile_shader(uint32_t type, const std::string& source) {
    // Stub - actual OpenGL shader compilation
    return 0;
}

} // namespace engine
