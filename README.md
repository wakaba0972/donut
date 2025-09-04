# ASCII 3D Renderer

A sophisticated ASCII-based 3D rendering engine that creates beautiful rotating 3D shapes using character-based graphics.

## 🎯 Features

- **Real-time 3D Rendering**: Uses z-buffer algorithm for proper depth rendering
- **Cross-platform**: Works on Windows, Linux, and macOS
- **Modular Architecture**: Clean separation of concerns with dedicated modules
- **Comprehensive Logging**: Built-in logging system for debugging and monitoring
- **Extensible Design**: Easy to add new 3D shapes and rendering modes
- **User Interface**: Interactive menu system for shape selection

## 📁 Project Structure

```
ASCII3DRenderer/
├── core/           # Core rendering engine
│   ├── renderer.h  # Header for rendering classes
│   └── renderer.cpp # Implementation of 3D rendering logic
├── ui/             # User interface components
│   ├── ui.h        # UI header
│   └── ui.cpp      # Menu and interaction handling
├── log/            # Logging system
│   ├── logger.h    # Logging interface
│   └── logger.cpp  # Logging implementation
├── doc/            # Documentation
├── examples/       # Example programs
├── build/          # Build artifacts (generated)
├── main.cpp        # Main application entry point
├── donut.cpp       # Original standalone donut implementation
├── CMakeLists.txt  # Build configuration
├── README.md       # This file
└── LICENSE         # License information
```

## 🚀 Quick Start

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher

### Building

```bash
# Clone the repository
git clone <repository-url>
cd donut

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the application
./ascii3d
```

### Alternative: Quick Build (Linux/macOS)

```bash
# Compile directly with g++
g++ -std=c++17 -O2 -o ascii3d main.cpp core/renderer.cpp ui/ui.cpp log/logger.cpp

# Run
./ascii3d
```

## 🎮 Usage

1. **Start the application**: Run `./ascii3d`
2. **View the menu**: The application will display available shapes and controls
3. **Watch the animation**: Currently displays a rotating donut (torus)
4. **Exit**: Press 'q' followed by Enter to quit

### Current Shapes

- ✅ **Donut (Torus)**: Fully implemented with smooth rotation
- 🚧 **Cube**: Coming soon
- 🚧 **Sphere**: Coming soon  
- 🚧 **Teapot**: Coming soon

## 🔧 Technical Details

### Rendering Algorithm

The engine uses a **z-buffer algorithm** with the following steps:

1. **Mathematical Model**: Each shape is defined parametrically
2. **3D Transformation**: Applies rotation matrices for animation
3. **Projection**: Projects 3D coordinates to 2D screen space
4. **Depth Testing**: Uses z-buffer to handle occlusion
5. **Lighting**: Simple lighting model for character selection
6. **Character Mapping**: Maps lighting intensity to ASCII characters: `.,-~:;=!*#$@`

### Architecture

- **Core Module**: Contains the rendering engine and shape definitions
- **UI Module**: Handles user interaction and display management
- **Log Module**: Provides comprehensive logging with multiple levels
- **Extensible Design**: Easy to add new shapes by implementing the `Shape3D` interface

## 📊 Logging

The application includes a sophisticated logging system:

- **Log Levels**: DEBUG, INFO, WARNING, ERROR
- **Dual Output**: Console and file logging
- **Timestamps**: Precise timestamping with milliseconds
- **Auto-rotation**: Prevents log files from growing too large

Log files are stored in the `log/` directory.

## 🛠 Development

### Adding New Shapes

1. Create a new class inheriting from `Shape3D`
2. Implement the `render()` and `update()` methods
3. Add the shape type to the `ShapeType` enum
4. Update the UI to include the new shape

### Example:

```cpp
class CubeRenderer : public Shape3D {
public:
    std::string render() override {
        // Implement cube rendering
    }
    
    void update() override {
        // Implement cube animation
    }
};
```

## 🎯 Future Enhancements

- [ ] **Image Upload**: Allow users to upload images for 3D conversion
- [ ] **More Shapes**: Cube, sphere, teapot, and custom models
- [ ] **Color Support**: Terminal color support for enhanced visuals
- [ ] **Interactive Controls**: Real-time rotation and zoom controls
- [ ] **Model Loading**: Support for loading 3D model files (OBJ, PLY)
- [ ] **Performance Optimization**: Multi-threading and SIMD optimization

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by the classic ASCII donut animation
- Z-buffer algorithm implementation
- Mathematical foundations from computer graphics literature

## 📞 Contact

For questions, suggestions, or contributions, please open an issue on GitHub.

---

**享受 ASCII 3D 渲染的樂趣！ (Enjoy ASCII 3D rendering!)**
