cmake_minimum_required(VERSION 3.20)
project(MyEngine VERSION 1.0.0 LANGUAGES CXX)

# --- C++17 standard ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Output directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- Dependencies via FetchContent ---
include(FetchContent)

# FetchContent for testing
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# --- Engine library ---
add_subdirectory(engine)

# --- Editor (Phase 13) ---
add_subdirectory(editor)

# --- Demo game (Phase 14) ---
add_subdirectory(games/demo_game)

# --- Tests ---
enable_testing()
add_subdirectory(tests)
