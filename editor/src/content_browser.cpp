#include "editor/content_browser.h"
#include <algorithm>
#include <filesystem>

namespace editor {

ContentBrowser::ContentBrowser() : m_current_directory(".") {
    refresh();
}

void ContentBrowser::draw() {
    draw_breadcrumb();
    draw_file_list();
}

void ContentBrowser::refresh() {
    m_entries.clear();
    try {
        for (const auto& entry : std::filesystem::directory_iterator(m_current_directory)) {
            m_entries.push_back(entry.path().filename().string());
        }
    } catch (...) {
        // Handle filesystem errors
    }
    std::sort(m_entries.begin(), m_entries.end());
}

void ContentBrowser::draw_breadcrumb() {
    // ImGui breadcrumb navigation
}

void ContentBrowser::draw_file_list() {
    // ImGui file list with icons
}

} // namespace editor
