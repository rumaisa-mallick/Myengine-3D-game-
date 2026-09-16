#pragma once

#include <string>
#include <vector>

namespace editor {

class EditorUI {
public:
    void init();
    void shutdown();
    void begin_frame();
    void end_frame();

    void draw_main_menu_bar();
    void draw_scene_hierarchy();
    void draw_inspector();
    void draw_content_browser();
    void draw_console();
    void draw_viewport();

private:
    bool m_show_hierarchy = true;
    bool m_show_inspector = true;
    bool m_show_content_browser = true;
    bool m_show_console = true;
    std::vector<std::string> m_console_messages;
};

} // namespace editor
