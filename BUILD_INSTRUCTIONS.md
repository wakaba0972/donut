# Quick Build Instructions

## Method 1: Using the Build Scripts (Recommended for quick start)

### Windows:
1. Double-click `build.bat` or run it from command prompt:
```cmd
build.bat
```

### Linux/Mac:
1. Make the script executable and run:
```bash
chmod +x build.sh
./build.sh
```

## Method 2: Manual Compilation

### All Platforms:
```bash
# Create log directory
mkdir -p log

# Compile all source files together
g++ -std=c++17 -Wall -Wextra main.cpp core/renderer.cpp log/logger.cpp ui/ui.cpp -o ascii3d

# Run the program
./ascii3d        # Linux/Mac
ascii3d.exe      # Windows
```

## Method 3: Using CMake (For advanced users)

```bash
mkdir build
cd build
cmake ..
make
./ascii3d
```

## Notes:
- Make sure you have g++ with C++17 support installed
- The program will create a `log/` directory for log files
- Press Ctrl+C to exit the animation when running