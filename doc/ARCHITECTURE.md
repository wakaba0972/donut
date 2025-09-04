# Architecture Documentation

## Overview

The ASCII 3D Renderer is built with a modular architecture that separates concerns into distinct components. This design makes the codebase maintainable, testable, and extensible.

## Core Components

### 1. Core Module (`core/`)

The core module contains the fundamental rendering engine and shape definitions.

#### `renderer.h` / `renderer.cpp`
- **DonutRenderer**: Implements the 3D donut rendering using z-buffer algorithm
- **Shape3D**: Abstract base class for all 3D shapes
- **ShapeType**: Enumeration of available shape types

Key features:
- Z-buffer depth testing
- Parametric surface generation
- Mathematical transformations
- Lighting calculations
- ASCII character mapping

### 2. UI Module (`ui/`)

The user interface module handles all user interaction and display management.

#### `ui.h` / `ui.cpp`
- **UserInterface**: Main UI controller
- Menu display and navigation
- Shape selection handling
- Render loop management

Key features:
- Cross-platform screen clearing
- Interactive menu system
- Real-time rendering loop
- User input handling

### 3. Logging Module (`log/`)

The logging module provides comprehensive logging capabilities.

#### `logger.h` / `logger.cpp`
- **Logger**: Singleton logger class
- **LogLevel**: Enumeration of log levels (DEBUG, INFO, WARNING, ERROR)
- Formatted message output
- File and console logging

Key features:
- Thread-safe logging
- Configurable log levels
- Timestamped messages
- Dual output (console + file)

## Data Flow

```
main.cpp
    ↓
UserInterface
    ↓
DonutRenderer
    ↓
Shape3D (abstract)
    ↓
ASCII Output
```

## Design Patterns

### 1. Singleton Pattern
- Used in the `Logger` class to ensure single instance
- Provides global access to logging functionality

### 2. Strategy Pattern
- `Shape3D` abstract class allows different rendering strategies
- Easy to add new shapes without modifying existing code

### 3. Template Method Pattern
- Common rendering pipeline with shape-specific implementations
- Consistent interface across different shapes

## Extension Points

### Adding New Shapes

1. Create a new class inheriting from `Shape3D`
2. Implement `render()` and `update()` methods
3. Add to `ShapeType` enum
4. Update UI to handle new shape

### Adding New Features

1. **Color Support**: Extend character mapping to include terminal colors
2. **Interactive Controls**: Add keyboard/mouse input for real-time manipulation
3. **File Loading**: Implement loaders for common 3D file formats
4. **Performance**: Add multi-threading and SIMD optimizations

## Memory Management

- Uses modern C++ RAII principles
- Smart pointers for automatic memory management
- No manual memory allocation/deallocation
- Exception-safe resource handling

## Cross-Platform Considerations

- Conditional compilation for platform-specific code
- Standard C++ libraries used where possible
- CMake build system for portability
- Platform-specific sleep and screen clearing functions

## Performance Characteristics

- **Time Complexity**: O(n²) for surface generation (where n is resolution)
- **Space Complexity**: O(w×h) for z-buffer and display buffer
- **Frame Rate**: ~20 FPS on modern hardware
- **Memory Usage**: ~50KB for buffers and lookup tables

## Testing Strategy

- Unit tests for core rendering functions
- Integration tests for UI workflows
- Cross-platform build verification
- Performance benchmarking

## Future Architecture Improvements

1. **Plugin System**: Dynamic loading of shape renderers
2. **Configuration System**: JSON/YAML configuration files
3. **Render Pipeline**: Configurable rendering stages
4. **Scene Management**: Multiple objects and camera controls