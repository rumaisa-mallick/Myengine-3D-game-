#include "editor/editor_ui.h"

namespace editor {

void EditorUI::init() {
    m_console_messages.push_back("Editor initialized");
}

void EditorUI::shutdown() {
}

void EditorUI::begin_frame() {
}

void EditorUI::end_frame() {
}

void EditorUI::draw_main_menu_bar() {
    // ImGui main menu bar
}

void EditorUI::draw_scene_hierarchy() {
    if (!m_show_hierarchy) return;
}

void EditorUI::draw_inspector() {
    if (!m_show_inspector) return;
}

void EditorUI::draw_content_browser() {
    if (!m_show_content_browser) return;
}

void EditorUI::draw_console() {
    if (!m_show_console) return;
}

void EditorUI::draw_viewport() {
}

} // namespace editor
