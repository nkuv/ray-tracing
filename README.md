# Ray Tracing Project

A simple 2D ray tracing demonstration using SFML.

## Project Structure

The project is organized into a clean, modular structure:

### Core Classes
- **Scene**: Manages game objects and rendering logic
- **Renderer**: Handles all ray tracing and rendering operations
- **RayTracer**: Implements real ray tracing with proper ray-object intersections
- **Ray**: Represents individual rays with mathematical properties
- **Sphere**: Represents a sphere object with ray intersection capabilities
- **Light**: Represents a light source with position and color
- **Utils**: Utility constants and helper functions

### Directory Structure
```
ray-tracing/
├── include/          # Header files
│   ├── scene.hpp     # Scene management header
│   ├── renderer.hpp  # Renderer and ray tracing header
│   ├── raytracer.hpp # Real ray tracer header
│   ├── ray.hpp       # Ray mathematics header
│   ├── sphere.hpp    # Sphere class header
│   ├── light.hpp     # Light class header
│   └── utils.hpp     # Utility constants and functions
├── src/              # Source files
│   ├── main.cpp      # Entry point with main game loop
│   ├── scene.cpp     # Scene management implementation
│   ├── renderer.cpp  # Renderer and ray tracing implementation
│   ├── raytracer.cpp # Real ray tracer implementation
│   ├── ray.cpp       # Ray mathematics implementation
│   ├── sphere.cpp    # Sphere class implementation
│   ├── light.cpp     # Light class implementation
│   └── utils.cpp     # Utility functions implementation
└── README.md         # This file
```

## Controls
- **Mouse**: Move the sphere (follows mouse with smooth movement)
- **Arrow Keys**: Move the light source
- **R Key**: Toggle ray display on/off
- **T Key**: Cycle through ray display modes:
  - **None**: No rays displayed
  - **Sphere Only**: Rays only to the sphere
  - **All Rays**: Rays in all directions from light source
  - **Both**: All rays + sphere rays
- **2 Key**: Toggle 2D scene mode (light fills screen, sphere casts shadows)
- **3 Key**: Toggle real ray tracing mode (proper ray-object intersections)
- **Close Window**: Close the application

## Building
This is a Visual Studio project. Open `ray-tracing.sln` and build the solution.

## Features
- Smooth sphere movement following mouse cursor
- Dynamic lighting based on distance from light source
- **Real Ray Tracing**: Proper ray-object intersections with mathematical accuracy
- **2D Scene Mode**: Light fills the entire screen with realistic shadows
- **Shadow Casting**: Sphere blocks light and creates dark shadow areas
- **Multiple ray display modes**: Choose what rays to visualize
- **All-direction ray casting**: See light rays in every direction
- **Ray visualization**: See light rays from source to sphere
- **Light radius indicator**: Visual representation of light reach
- **Intensity-based ray colors**: Rays change color based on lighting intensity
- Modular, extensible code structure
- Clean separation of concerns between game logic, rendering, and input handling
- Dedicated renderer for ray tracing calculations

## Real Ray Tracing Mode
When enabled (press **3**), the renderer switches to real ray tracing mode featuring:
- **Mathematical ray-sphere intersections** using quadratic formula
- **Proper shadow calculations** with shadow rays
- **Ambient and diffuse lighting** with realistic attenuation
- **Pixel-perfect rendering** with individual ray tracing per pixel
- **Material properties** for realistic surface rendering
- **Professional ray tracing algorithms** used in modern graphics

## 2D Scene Mode
When enabled (press **2**), the renderer switches to a 2D scene mode where:
- **Light fills the entire screen** with warm, distance-based lighting
- **Sphere casts realistic shadows** by blocking light from the source
- **Shadow calculation** uses geometric ray-sphere intersection
- **Performance optimized** with pixel sampling for smooth rendering
- **Visual feedback** shows sphere outline and light source position