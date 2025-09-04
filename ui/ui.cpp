#include "ui.h"
#include <iostream>
#include <thread>
#include <chrono>

// Cross-platform compatibility
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

namespace ASCII3D {
    
    UserInterface::UserInterface() 
        : renderer(std::make_unique<DonutRenderer>())
        , currentShape(ShapeType::DONUT)
        , running(false) {
        LOG_INFO("User Interface initialized");
    }
    
    void UserInterface::clearScreen() {
        system(CLEAR_SCREEN);
    }
    
    void UserInterface::displayMenu() {
        std::cout << "==========================================\n";
        std::cout << "      ASCII 3D Shape Renderer v1.0      \n";
        std::cout << "==========================================\n";
        std::cout << "Available Shapes:\n";
        std::cout << "1. Donut (Currently implemented)\n";
        std::cout << "2. Cube (Coming soon)\n";
        std::cout << "3. Sphere (Coming soon)\n";
        std::cout << "4. Teapot (Coming soon)\n";
        std::cout << "\nControls:\n";
        std::cout << "- Press 'q' to quit\n";
        std::cout << "- Press any other key to continue\n";
        std::cout << "==========================================\n\n";
    }
    
    void UserInterface::displayShapeInfo() {
        std::cout << "Current Shape: ";
        switch(currentShape) {
            case ShapeType::DONUT:
                std::cout << "Rotating Donut (Torus)\n";
                break;
            case ShapeType::CUBE:
                std::cout << "Cube (Not implemented yet)\n";
                break;
            case ShapeType::SPHERE:
                std::cout << "Sphere (Not implemented yet)\n";
                break;
            case ShapeType::TEAPOT:
                std::cout << "Teapot (Not implemented yet)\n";
                break;
        }
        std::cout << "Rendering method: Z-buffer with ASCII characters\n";
        std::cout << "Characters used: .,-~:;=!*#$@\n\n";
    }
    
    void UserInterface::run() {
        LOG_INFO("Starting ASCII 3D Renderer");
        running = true;
        
        clearScreen();
        displayMenu();
        displayShapeInfo();
        
        std::cout << "Press Enter to start rendering...\n";
        std::cin.get();
        
        LOG_INFO("Beginning render loop");
        while(running) {
            clearScreen();
            
            // Update and render the current shape
            renderer->update();
            std::cout << renderer->render();
            
            std::cout << "\nPress 'q' + Enter to quit, or just Enter to continue...\n";
            
            // Sleep for a short time
            SLEEP(50);
            
            // Check for input (non-blocking would be better, but keeping it simple)
            // For now, the animation will continue without input checking
        }
        
        LOG_INFO("Render loop ended");
    }
    
    void UserInterface::stop() {
        running = false;
        LOG_INFO("User Interface stopped");
    }
    
    void UserInterface::setShape(ShapeType shape) {
        currentShape = shape;
        LOG_INFO("Shape changed to: " + std::to_string(static_cast<int>(shape)));
    }
    
    ShapeType UserInterface::getCurrentShape() const {
        return currentShape;
    }
}