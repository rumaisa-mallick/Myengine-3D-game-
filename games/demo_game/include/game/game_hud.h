#pragma once

#include "engine/engine.h"

namespace game {

class GameHUD {
public:
    void init();
    void update(float dt);
    void draw();
    void shutdown();

    void set_score(int score) { m_score = score; }
    void set_health(float health) { m_health = health; }
    void add_message(const std::string& msg);

private:
    int m_score = 0;
    float m_health = 100.0f;
    std::vector<std::string> m_messages;
    float m_message_timer = 0.0f;
};

} // namespace game
