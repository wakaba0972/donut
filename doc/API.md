# API Documentation

## Core API

### DonutRenderer

The main rendering class for 3D donut (torus) shapes.

```cpp
class DonutRenderer {
public:
    DonutRenderer();
    void update();
    std::string render();
    void reset();
};
```

#### Methods

##### `DonutRenderer()`
Constructor that initializes the renderer.
- Builds trigonometric lookup tables
- Resets buffers and display arrays
- Sets initial rotation angles to 0

##### `void update()`
Updates the 3D model for the next frame.
- Increments rotation angles A and B
- Recalculates all surface points
- Updates z-buffer and display buffer
- Applies lighting calculations

##### `std::string render()`
Returns the current frame as an ASCII string.
- **Returns**: Multi-line string containing ASCII art
- **Format**: 22 rows × 40 columns
- **Characters**: `.,-~:;=!*#$@` (light to dark)

##### `void reset()`
Clears all buffers.
- Zeroes z-buffer array
- Fills display buffer with spaces

### Shape3D (Abstract)

Base class for all 3D shapes.

```cpp
class Shape3D {
public:
    virtual ~Shape3D() = default;
    virtual std::string render() = 0;
    virtual void update() = 0;
};
```

#### Methods

##### `virtual std::string render() = 0`
Pure virtual method to render the shape.
- **Returns**: ASCII representation of the shape

##### `virtual void update() = 0`
Pure virtual method to update the shape's state.

## UI API

### UserInterface

Main user interface controller.

```cpp
class UserInterface {
public:
    UserInterface();
    void run();
    void stop();
    void setShape(ShapeType shape);
    ShapeType getCurrentShape() const;
};
```

#### Methods

##### `UserInterface()`
Constructor that initializes the UI.
- Creates DonutRenderer instance
- Sets default shape to DONUT
- Initializes logging

##### `void run()`
Starts the main application loop.
- Displays welcome menu
- Begins render loop
- Handles basic user interaction

##### `void stop()`
Stops the application.
- Sets running flag to false
- Logs shutdown message

##### `void setShape(ShapeType shape)`
Changes the current shape.
- **Parameters**: `shape` - The shape type to set
- **Note**: Currently only DONUT is implemented

##### `ShapeType getCurrentShape() const`
Returns the currently selected shape.
- **Returns**: Current ShapeType enum value

## Logging API

### Logger

Singleton logging system.

```cpp
class Logger {
public:
    static Logger& getInstance();
    void setLevel(LogLevel level);
    void log(LogLevel level, const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
};
```

#### Methods

##### `static Logger& getInstance()`
Returns the singleton logger instance.
- **Returns**: Reference to the global logger

##### `void setLevel(LogLevel level)`
Sets the minimum log level.
- **Parameters**: `level` - Minimum level to log
- **Levels**: DEBUG, INFO, WARNING, ERROR

##### `void log(LogLevel level, const std::string& message)`
Logs a message at the specified level.
- **Parameters**: 
  - `level` - Log level
  - `message` - Message to log

##### Convenience Methods
- `debug(message)` - Logs at DEBUG level
- `info(message)` - Logs at INFO level  
- `warning(message)` - Logs at WARNING level
- `error(message)` - Logs at ERROR level

#### Macros

Convenience macros for logging:

```cpp
LOG_DEBUG("Debug message");
LOG_INFO("Info message");
LOG_WARNING("Warning message");
LOG_ERROR("Error message");
```

## Enumerations

### ShapeType

Available 3D shapes.

```cpp
enum class ShapeType {
    DONUT,    // Implemented
    CUBE,     // Coming soon
    SPHERE,   // Coming soon
    TEAPOT    // Coming soon
};
```

### LogLevel

Logging levels in order of severity.

```cpp
enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};
```

## Constants

### Rendering Constants

```cpp
static constexpr int WIDTH = 40;   // Display width
static constexpr int HEIGHT = 22;  // Display height
```

### Character Set

The lighting characters from darkest to brightest:
```
".,-~:;=!*#$@"
```

## Example Usage

### Basic Rendering

```cpp
#include "core/renderer.h"

// Create renderer
ASCII3D::DonutRenderer renderer;

// Render loop
while (running) {
    renderer.update();
    std::cout << renderer.render();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}
```

### Logging

```cpp
#include "log/logger.h"

// Set log level
ASCII3D::Logger::getInstance().setLevel(ASCII3D::LogLevel::DEBUG);

// Log messages
LOG_INFO("Application started");
LOG_DEBUG("Debug information");
LOG_WARNING("Something might be wrong");
LOG_ERROR("An error occurred");
```

### Full Application

```cpp
#include "ui/ui.h"

int main() {
    auto ui = std::make_unique<ASCII3D::UserInterface>();
    ui->run();
    return 0;
}
```