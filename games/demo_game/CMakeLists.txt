set(GAME_SOURCES
    src/main.cpp
    src/demo_game.cpp
    src/player_controller.cpp
    src/enemy_controller.cpp
    src/game_hud.cpp
)

add_executable(demo_game ${GAME_SOURCES})

target_include_directories(demo_game
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(demo_game PRIVATE engine)
target_compile_features(demo_game PRIVATE cxx_std_17)
