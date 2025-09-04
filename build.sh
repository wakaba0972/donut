#!/bin/bash

echo "Building ASCII 3D Renderer..."
echo

# Create log directory if it doesn't exist
mkdir -p log

# Compile all source files together
g++ -std=c++17 -Wall -Wextra main.cpp core/renderer.cpp log/logger.cpp ui/ui.cpp -o ascii3d

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo
    echo "Running ASCII 3D Renderer..."
    echo "Press Ctrl+C to exit when done."
    echo
    ./ascii3d
else
    echo "Build failed! Please check the error messages above."
    exit 1
fi