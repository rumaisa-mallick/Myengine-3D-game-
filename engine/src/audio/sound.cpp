#include "engine/audio/sound.h"
#include "engine/core/logger.h"

namespace engine {

Sound::Sound(const std::string& path) {
    LOG_DEBUG("Loading sound: %s", path.c_str());
    // OpenAL buffer loading from WAV/OGG would go here
    // alGenBuffers(1, &m_buffer_id);
    // alGenSources(1, &m_source_id);
    m_loaded = true;
}

Sound::~Sound() {
    if (m_loaded) {
        // alDeleteSources(1, &m_source_id);
        // alDeleteBuffers(1, &m_buffer_id);
    }
}

void Sound::play() {
    if (!m_loaded) return;
    // alSourcePlay(m_source_id);
}

void Sound::pause() {
    if (!m_loaded) return;
    // alSourcePause(m_source_id);
}

void Sound::stop() {
    if (!m_loaded) return;
    // alSourceStop(m_source_id);
}

void Sound::set_looping(bool loop) {
    if (!m_loaded) return;
    // alSourcei(m_source_id, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}

void Sound::set_volume(float volume) {
    if (!m_loaded) return;
    // alSourcef(m_source_id, AL_GAIN, volume);
}

bool Sound::is_playing() const {
    // ALint state;
    // alGetSourcei(m_source_id, AL_SOURCE_STATE, &state);
    // return state == AL_PLAYING;
    return false;
}

float Sound::get_duration() const {
    // ALint size, freq, channels, bits;
    // alGetBufferi(m_buffer_id, AL_SIZE, &size);
    // alGetBufferi(m_buffer_id, AL_FREQUENCY, &freq);
    // alGetBufferi(m_buffer_id, AL_CHANNELS, &channels);
    // alGetBufferi(m_buffer_id, AL_BITS, &bits);
    // return static_cast<float>(size) / (freq * channels * bits / 8);
    return 0.0f;
}

} // namespace engine
