#include "engine/core/timer.h"

namespace engine {

Timer::Timer() {
    reset();
}

void Timer::reset() {
    m_start = Clock::now();
    m_last_frame = m_start;
    m_delta = 0.0f;
    m_fps = 0.0f;
    m_fps_timer = 0.0f;
    m_frame_count = 0;
}

float Timer::elapsed() const {
    auto now = Clock::now();
    return std::chrono::duration<float>(now - m_start).count();
}

float Timer::delta_time() const {
    return m_delta;
}

void Timer::update() {
    auto now = Clock::now();
    m_delta = std::chrono::duration<float>(now - m_last_frame).count();
    m_last_frame = now;

    m_frame_count++;
    m_fps_timer += m_delta;
    if (m_fps_timer >= 1.0f) {
        m_fps = static_cast<float>(m_frame_count) / m_fps_timer;
        m_frame_count = 0;
        m_fps_timer = 0.0f;
    }
}

float Timer::fps() const {
    return m_fps;
}

float Timer::frame_time() const {
    return m_delta * 1000.0f; // Return in milliseconds
}

} // namespace engine
