set(TEST_SOURCES
    src/test_main.cpp
    src/test_math.cpp
    src/test_ecs.cpp
    src/test_resource.cpp
    src/test_scene.cpp
)

add_executable(engine_tests ${TEST_SOURCES})

target_include_directories(engine_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine_tests PRIVATE engine GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(engine_tests)
