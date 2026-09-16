#pragma once

#include <string>
#include <cstdint>

namespace engine {

class Sound {
public:
    Sound() = default;
    Sound(const std::string& path);
    ~Sound();

    void play();
    void pause();
    void stop();
    void set_looping(bool loop);
    void set_volume(float volume);

    bool is_playing() const;
    float get_duration() const;

private:
    uint32_t m_buffer_id = 0;
    uint32_t m_source_id = 0;
    bool m_loaded = false;
};

} // namespace engine
