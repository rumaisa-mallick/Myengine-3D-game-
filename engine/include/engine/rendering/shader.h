#pragma once

#include <string>
#include <cstdint>

namespace engine {

class Shader {
public:
    Shader() = default;
    Shader(const std::string& vertex_src, const std::string& fragment_src);
    ~Shader();

    void bind() const;
    void unbind() const;

    void set_int(const std::string& name, int value);
    void set_float(const std::string& name, float value);
    void set_vec3(const std::string& name, float x, float y, float z);
    void set_mat4(const std::string& name, const float* data);

    uint32_t get_id() const { return m_program_id; }

    static Shader from_files(const std::string& vertex_path, const std::string& fragment_path);
    static Shader create_default();

private:
    uint32_t m_program_id = 0;
    uint32_t compile_shader(uint32_t type, const std::string& source);
};

} // namespace engine
