#pragma once

#include <chrono>

namespace engine {

class Timer {
public:
    Timer();

    void reset();
    float elapsed() const;
    float delta_time() const;
    void update();

    float fps() const;
    float frame_time() const;

private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    TimePoint m_start;
    TimePoint m_last_frame;
    float m_delta = 0.0f;
    float m_fps = 0.0f;
    float m_fps_timer = 0.0f;
    uint32_t m_frame_count = 0;
};

} // namespace engine
