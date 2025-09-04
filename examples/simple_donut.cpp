#include "../core/renderer.h"
#include "../log/logger.h"
#include <iostream>
#include <chrono>
#include <thread>

// Cross-platform compatibility
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

/**
 * Simple example demonstrating basic donut rendering
 * without the full UI system.
 */
int main() {
    // Initialize logging for this example
    ASCII3D::Logger::getInstance().setLevel(ASCII3D::LogLevel::INFO);
    LOG_INFO("Starting simple donut example");
    
    try {
        // Create a donut renderer
        ASCII3D::DonutRenderer renderer;
        
        std::cout << "Simple Donut Renderer Example\n";
        std::cout << "=============================\n";
        std::cout << "This will render a rotating donut for 100 frames.\n";
        std::cout << "Press Ctrl+C to exit early.\n\n";
        
        // Render for 100 frames
        for (int frame = 0; frame < 100; ++frame) {
            // Clear screen
            system(CLEAR_SCREEN);
            
            // Update and render
            renderer.update();
            std::cout << renderer.render();
            
            // Display frame info
            std::cout << "Frame: " << frame + 1 << "/100\n";
            std::cout << "Press Ctrl+C to exit\n";
            
            // Sleep for smooth animation (20 FPS)
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        std::cout << "\nAnimation complete!\n";
        LOG_INFO("Simple donut example completed successfully");
        
    } catch (const std::exception& e) {
        LOG_ERROR("Error in simple donut example: " + std::string(e.what()));
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}