#pragma once

#include "engine/audio/sound.h"
#include "engine/math/math_utils.h"
#include <string>
#include <memory>
#include <unordered_map>

namespace engine {

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    void init();
    void shutdown();
    void update();

    std::shared_ptr<Sound> load_sound(const std::string& path);
    void set_master_volume(float volume);
    float get_master_volume() const { return m_master_volume; }

    void set_listener_position(Vec3 position);
    void set_listener_orientation(Vec3 forward, Vec3 up);

private:
    std::unordered_map<std::string, std::shared_ptr<Sound>> m_sounds;
    float m_master_volume = 1.0f;
    bool m_initialized = false;
    void* m_device = nullptr;
    void* m_context = nullptr;
};

} // namespace engine
