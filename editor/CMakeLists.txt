set(EDITOR_SOURCES
    src/editor_app.cpp
    src/editor_ui.cpp
    src/editor_camera.cpp
    src/scene_hierarchy.cpp
    src/inspector.cpp
    src/content_browser.cpp
)

add_executable(editor ${EDITOR_SOURCES})

target_include_directories(editor
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(editor PRIVATE engine)
target_compile_features(editor PRIVATE cxx_std_17)
