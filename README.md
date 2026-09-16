# MyEngine

A C++17 game engine with Entity Component System (ECS) architecture.

## Project Structure

```
MyEngine/
├── CMakeLists.txt          # Root build configuration
├── engine/                 # Core engine library (static)
│   ├── include/engine/     # Public headers
│   │   ├── core/           # Application, Window, Input, Logger, Timer, Event
│   │   ├── math/           # Vec2, Vec3, Vec4, Mat4, Quaternion
│   │   ├── ecs/            # Entity, Component, System, World
│   │   ├── rendering/      # Renderer, Shader, Texture, Mesh, Camera
│   │   ├── physics/        # PhysicsWorld, RigidBody, Collider
│   │   ├── audio/          # AudioEngine, Sound
│   │   ├── resource/       # ResourceManager, AssetLoader
│   │   └── scene/          # Scene, SceneManager
│   └── src/                # Implementation files
├── editor/                 # Level editor application (Phase 13)
│   ├── include/editor/     # Editor headers
│   └── src/                # Editor implementation
├── games/demo_game/        # Demo game (Phase 14)
│   ├── include/game/       # Game headers
│   └── src/                # Game implementation
└── tests/                  # Unit tests (Google Test)
    └── src/                # Test files
```

## Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Running Tests

```bash
cd build
ctest --output-on-failure
```

## Engine Features

- **ECS Architecture** - Entity Component System with type-safe component queries
- **Math Library** - Vec2/3/4, Mat4, Quaternion with common operations
- **Rendering** - Shader, Texture, Mesh, Camera abstraction (OpenGL backend stubs)
- **Physics** - RigidBody, Collider, PhysicsWorld with collision detection
- **Audio** - Sound loading and playback (OpenAL backend stubs)
- **Resource Management** - Centralized asset loading and caching
- **Scene System** - Scene creation, loading, and management
- **Event System** - Publish/subscribe event bus
- **Input System** - Keyboard and mouse input handling
- **Logging** - Configurable logging with file output

## Editor Features

- Scene hierarchy view
- Entity inspector
- Content browser
- Editor camera with orbit controls

## Demo Game

- Player controller with WASD movement and jumping
- Enemy AI with target tracking
- Game HUD with score and health display

## Architecture

The engine uses a data-oriented ECS design where:
- **Entities** are lightweight IDs
- **Components** are plain data structs
- **Systems** contain logic and iterate over component queries
- **World** manages entity lifecycle and component storage

## Dependencies

- **Google Test** - Fetched via CMake FetchContent for unit testing
