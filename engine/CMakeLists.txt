set(ENGINE_SOURCES
    src/core/logger.cpp
    src/core/application.cpp
    src/core/window.cpp
    src/core/input.cpp
    src/core/timer.cpp
    src/core/event.cpp
    src/math/math_utils.cpp
    src/ecs/entity.cpp
    src/ecs/world.cpp
    src/ecs/component.cpp
    src/ecs/system.cpp
    src/rendering/renderer.cpp
    src/rendering/shader.cpp
    src/rendering/texture.cpp
    src/rendering/mesh.cpp
    src/rendering/camera.cpp
    src/physics/physics_world.cpp
    src/physics/rigid_body.cpp
    src/physics/collider.cpp
    src/audio/audio_engine.cpp
    src/audio/sound.cpp
    src/resource/resource_manager.cpp
    src/resource/asset_loader.cpp
    src/scene/scene.cpp
    src/scene/scene_manager.cpp
)

add_library(engine STATIC ${ENGINE_SOURCES})

target_include_directories(engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(engine PUBLIC cxx_std_17)
