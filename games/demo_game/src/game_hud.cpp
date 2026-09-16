#include "game/game_hud.h"

namespace game {

void GameHUD::init() {
    m_score = 0;
    m_health = 100.0f;
    m_messages.clear();
}

void GameHUD::update(float dt) {
    m_message_timer -= dt;
    if (m_message_timer <= 0 && !m_messages.empty()) {
        m_messages.erase(m_messages.begin());
        m_message_timer = 2.0f;
    }
}

void GameHUD::draw() {
    // ImGui HUD drawing
    // Score display
    // Health bar
    // Messages
}

void GameHUD::shutdown() {
    m_messages.clear();
}

void GameHUD::add_message(const std::string& msg) {
    m_messages.push_back(msg);
    if (m_messages.size() > 5) {
        m_messages.erase(m_messages.begin());
    }
    m_message_timer = 3.0f;
}

} // namespace game
