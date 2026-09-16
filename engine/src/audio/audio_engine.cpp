#include "engine/audio/audio_engine.h"
#include "engine/core/logger.h"

namespace engine {

AudioEngine::AudioEngine() {
    LOG_INFO("AudioEngine created");
}

AudioEngine::~AudioEngine() {
    shutdown();
}

void AudioEngine::init() {
    if (m_initialized) return;
    LOG_INFO("AudioEngine initialized");
    // OpenAL initialization would go here
    // m_device = alcOpenDevice(nullptr);
    // m_context = alcCreateContext((ALCdevice*)m_device, nullptr);
    m_initialized = true;
}

void AudioEngine::shutdown() {
    if (!m_initialized) return;
    m_sounds.clear();
    // alcDestroyContext((ALCcontext*)m_context);
    // alcCloseDevice((ALCdevice*)m_device);
    m_initialized = false;
    LOG_INFO("AudioEngine shut down");
}

void AudioEngine::update() {
    // Update spatial audio, streaming, etc.
}

std::shared_ptr<Sound> AudioEngine::load_sound(const std::string& path) {
    auto it = m_sounds.find(path);
    if (it != m_sounds.end()) {
        return it->second;
    }

    auto sound = std::make_shared<Sound>(path);
    m_sounds[path] = sound;
    return sound;
}

void AudioEngine::set_master_volume(float volume) {
    m_master_volume = volume;
    // alListenerf(AL_GAIN, volume);
}

void AudioEngine::set_listener_position(Vec3 position) {
    // alListener3f(AL_POSITION, position.x, position.y, position.z);
}

void AudioEngine::set_listener_orientation(Vec3 forward, Vec3 up) {
    float orientation[] = {forward.x, forward.y, forward.z, up.x, up.y, up.z};
    // alListenerfv(AL_ORIENTATION, orientation);
}

} // namespace engine
