# Ray Tracing Project

A simple 2D ray tracing demonstration using SFML.

## Project Structure

The project is organized into a clean, modular structure:

### Core Classes
- **Game**: Main game engine that manages the window and game loop
- **Scene**: Manages game objects and rendering logic
- **Sphere**: Represents a sphere object with lighting calculations
- **Light**: Represents a light source with position and color

### Directory Structure
```
ray-tracing/
├── include/          # Header files
│   ├── game.hpp      # Game engine header
│   ├── scene.hpp     # Scene management header
│   ├── sphere.hpp    # Sphere class header
│   ├── light.hpp     # Light class header
│   └── utils.hpp     # Utility constants and functions
├── src/              # Source files
│   ├── main.cpp      # Entry point
│   ├── game.cpp      # Game engine implementation
│   ├── scene.cpp     # Scene management implementation
│   ├── sphere.cpp    # Sphere class implementation
│   ├── light.cpp     # Light class implementation
│   └── utils.cpp     # Utility functions implementation
└── README.md         # This file
```

## Controls
- **Mouse**: Move the sphere (follows mouse with smooth movement)
- **Arrow Keys**: Move the light source
- **Close Window**: Close the application

## Building
This is a Visual Studio project. Open `ray-tracing.sln` and build the solution.

## Features
- Smooth sphere movement following mouse cursor
- Dynamic lighting based on distance from light source
- Modular, extensible code structure
- Clean separation of concerns between game logic, rendering, and input handling