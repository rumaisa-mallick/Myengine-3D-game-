#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include <any>

namespace engine {

class Event {
public:
    using Callback = std::function<void(const std::any&)>;

    explicit Event(const std::string& name) : m_name(name) {}

    const std::string& get_name() const { return m_name; }
    void set_data(std::any data) { m_data = std::move(data); }
    const std::any& get_data() const { return m_data; }

private:
    std::string m_name;
    std::any m_data;
};

class EventBus {
public:
    static EventBus& instance();

    uint32_t subscribe(const std::string& event_name, Event::Callback callback);
    void unsubscribe(uint32_t id);
    void dispatch(const Event& event);

private:
    EventBus() = default;

    struct Subscription {
        uint32_t id;
        Event::Callback callback;
    };

    std::unordered_map<std::string, std::vector<Subscription>> m_subscriptions;
    uint32_t m_next_id = 0;
};

} // namespace engine
