#pragma once

#include <string>
#include <vector>

namespace editor {

class ContentBrowser {
public:
    ContentBrowser();
    void draw();

private:
    std::string m_current_directory;
    std::vector<std::string> m_entries;

    void refresh();
    void draw_breadcrumb();
    void draw_file_list();
};

} // namespace editor
