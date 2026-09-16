#include "engine/core/event.h"

namespace engine {

EventBus& EventBus::instance() {
    static EventBus s_instance;
    return s_instance;
}

uint32_t EventBus::subscribe(const std::string& event_name, Event::Callback callback) {
    uint32_t id = m_next_id++;
    m_subscriptions[event_name].push_back({id, std::move(callback)});
    return id;
}

void EventBus::unsubscribe(uint32_t id) {
    for (auto& [name, subs] : m_subscriptions) {
        subs.erase(std::remove_if(subs.begin(), subs.end(),
            [id](const Subscription& s) { return s.id == id; }),
            subs.end());
    }
}

void EventBus::dispatch(const Event& event) {
    auto it = m_subscriptions.find(event.get_name());
    if (it != m_subscriptions.end()) {
        for (auto& sub : it->second) {
            sub.callback(event.get_data());
        }
    }
}

} // namespace engine
