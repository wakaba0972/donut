@echo off
echo Building ASCII 3D Renderer...
echo.

REM Create log directory if it doesn't exist
if not exist "log" mkdir log

REM Compile all source files together
g++ -std=c++17 -Wall -Wextra main.cpp core/renderer.cpp log/logger.cpp ui/ui.cpp -o ascii3d.exe

if %ERRORLEVEL% EQU 0 (
    echo Build successful! 
    echo.
    echo Running ASCII 3D Renderer...
    echo Press Ctrl+C to exit when done.
    echo.
    ascii3d.exe
) else (
    echo Build failed! Please check the error messages above.
    pause
)