#include "ui.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
        std::cout << "1. Donut (Torus)\n";
        std::cout << "2. Cube\n";
        std::cout << "3. Sphere\n";
        std::cout << "4. Teapot\n";
        std::cout << "\nControls during animation:\n";
        std::cout << "- Press 'q' + Enter to quit animation\n";
        std::cout << "- Press Enter to continue animation\n";
        std::cout << "==========================================\n\n";
    }
    
    void UserInterface::displayShapeInfo() {
        std::cout << "Current Shape: ";
        switch(currentShape) {
            case ShapeType::DONUT:
                std::cout << "Rotating Donut (Torus)\n";
                break;
            case ShapeType::CUBE:
                std::cout << "Rotating Cube\n";
                break;
            case ShapeType::SPHERE:
                std::cout << "Rotating Sphere\n";
                break;
            case ShapeType::TEAPOT:
                std::cout << "Rotating Teapot\n";
                break;
        }
        std::cout << "Rendering method: Z-buffer with ASCII characters\n";
        std::cout << "Characters used: .,-~:;=!*#$@\n\n";
    }
    
    void UserInterface::run() {
        LOG_INFO("Starting ASCII 3D Renderer");
        running = true;
        
        // Show main menu first
        while(running) {
            clearScreen();
            displayMenu();
            displayShapeInfo();
            
            std::cout << "Select an option:\n";
            std::cout << "1. Start Donut animation\n";
            std::cout << "2. Start Cube animation\n";
            std::cout << "3. Start Sphere animation\n";
            std::cout << "4. Start Teapot animation\n";
            std::cout << "q. Quit\n";
            std::cout << "Your choice: ";
            
            std::string choice;
            std::getline(std::cin, choice);
            
            if (choice == "q" || choice == "Q") {
                running = false;
                break;
            } else if (choice == "1") {
                currentShape = ShapeType::DONUT;
                runAnimation();
            } else if (choice == "2") {
                currentShape = ShapeType::CUBE;
                runAnimation();
            } else if (choice == "3") {
                currentShape = ShapeType::SPHERE;
                runAnimation();
            } else if (choice == "4") {
                currentShape = ShapeType::TEAPOT;
                runAnimation();
            } else {
                std::cout << "Invalid choice. Press Enter to continue...\n";
                std::cin.get();
            }
        }
        
        LOG_INFO("Application ended");
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
    
    void UserInterface::runAnimation() {
        LOG_INFO("Starting animation for shape: " + std::to_string(static_cast<int>(currentShape)));
        
        clearScreen();
        std::cout << "Starting animation... Press 'q' + Enter to return to menu\n";
        std::cout << "Press Enter to begin...\n";
        std::cin.get();
        
        bool animating = true;
        int frameCount = 0;
        
        while(animating && running) {
            clearScreen();
            
            // Update and render based on current shape
            switch(currentShape) {
                case ShapeType::DONUT:
                    renderer->update();
                    std::cout << renderer->render();
                    break;
                case ShapeType::CUBE:
                    std::cout << renderCube(frameCount);
                    break;
                case ShapeType::SPHERE:
                    std::cout << renderSphere(frameCount);
                    break;
                case ShapeType::TEAPOT:
                    std::cout << renderTeapot(frameCount);
                    break;
            }
            
            std::cout << "\n[Frame " << frameCount << "] ";
            std::cout << "Press 'q' + Enter to return to menu, or just Enter to continue...\n";
            
            frameCount++;
            
            // Use a timeout for input to allow animation to continue
            SLEEP(100);
            
            // Simple input check - this could be improved with non-blocking input
            // For now, let's run 200 frames then pause for input
            if (frameCount % 200 == 0) {
                std::cout << "Animation paused. Press Enter to continue or 'q' + Enter to quit: ";
                std::string input;
                std::getline(std::cin, input);
                if (input == "q" || input == "Q") {
                    animating = false;
                }
            }
        }
        
        LOG_INFO("Animation ended");
    }
    
    std::string UserInterface::renderCube(int frame) {
        static constexpr int WIDTH = 40;
        static constexpr int HEIGHT = 22;
        std::string result;
        
        // Simple rotating cube using ASCII art
        float angle = frame * 0.05f;
        float sinA = sin(angle);
        float cosA = cos(angle);
        
        // Clear the display
        char display[HEIGHT][WIDTH];
        for(int j = 0; j < HEIGHT; j++) {
            for(int i = 0; i < WIDTH; i++) {
                display[j][i] = ' ';
            }
        }
        
        // Draw cube vertices and edges
        float vertices[8][3] = {
            {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},  // Back face
            {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}       // Front face
        };
        
        // Rotate and project vertices
        for(int v = 0; v < 8; v++) {
            float x = vertices[v][0];
            float y = vertices[v][1];
            float z = vertices[v][2];
            
            // Rotate around Y axis
            float rx = x * cosA - z * sinA;
            // float rz = x * sinA + z * cosA;  // Not used for projection, commenting out
            
            // Project to 2D
            int px = WIDTH/2 + (int)(rx * 8);
            int py = HEIGHT/2 + (int)(y * 4);
            
            if(px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                display[py][px] = '*';
            }
        }
        
        // Draw some edges
        char edgeChar = '#';
        for(int i = 0; i < WIDTH; i++) {
            for(int j = 0; j < HEIGHT; j++) {
                float x = (i - WIDTH/2) / 8.0f;
                float y = (j - HEIGHT/2) / 4.0f;
                
                // Simple cube outline
                if((abs(x) > 0.8 && abs(x) < 1.2 && abs(y) < 1.0) ||
                   (abs(y) > 0.8 && abs(y) < 1.2 && abs(x) < 1.0)) {
                    display[j][i] = edgeChar;
                }
            }
        }
        
        // Convert to string
        for(int j = 0; j < HEIGHT; j++) {
            for(int i = 0; i < WIDTH; i++) {
                result += display[j][i];
            }
            result += '\n';
        }
        
        return result;
    }
    
    std::string UserInterface::renderSphere(int frame) {
        static constexpr int WIDTH = 40;
        static constexpr int HEIGHT = 22;
        std::string result;
        
        float angle = frame * 0.03f;
        
        // Clear the display
        char display[HEIGHT][WIDTH];
        for(int j = 0; j < HEIGHT; j++) {
            for(int i = 0; i < WIDTH; i++) {
                display[j][i] = ' ';
            }
        }
        
        // Draw sphere using parametric equations
        for(int phi = 0; phi < 180; phi += 5) {
            for(int theta = 0; theta < 360; theta += 8) {
                float phiRad = phi * M_PI / 180.0f;
                float thetaRad = (theta + angle * 50) * M_PI / 180.0f;
                
                float x = sin(phiRad) * cos(thetaRad);
                float y = cos(phiRad);
                float z = sin(phiRad) * sin(thetaRad);
                
                // Apply rotation
                float rotX = x * cos(angle) - z * sin(angle);
                float rotZ = x * sin(angle) + z * cos(angle);
                
                // Project to 2D
                int px = WIDTH/2 + (int)(rotX * 12);
                int py = HEIGHT/2 + (int)(y * 8);
                
                if(px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                    // Vary character based on depth
                    char chars[] = ".,-~:;=!*#$@";
                    int charIndex = (int)((rotZ + 1) * 6);
                    charIndex = charIndex < 0 ? 0 : (charIndex > 11 ? 11 : charIndex);
                    display[py][px] = chars[charIndex];
                }
            }
        }
        
        // Convert to string
        for(int j = 0; j < HEIGHT; j++) {
            for(int i = 0; i < WIDTH; i++) {
                result += display[j][i];
            }
            result += '\n';
        }
        
        return result;
    }
    
    std::string UserInterface::renderTeapot(int frame) {
        static constexpr int WIDTH = 40;
        static constexpr int HEIGHT = 22;
        std::string result;
        
        float angle = frame * 0.04f;
        
        // Clear the display
        char display[HEIGHT][WIDTH];
        for(int j = 0; j < HEIGHT; j++) {
            for(int i = 0; i < WIDTH; i++) {
                display[j][i] = ' ';
            }
        }
        
        // Simplified teapot using basic shapes
        // Body (ellipse)
        for(int i = 0; i < WIDTH; i++) {
            for(int j = 0; j < HEIGHT; j++) {
                float x = (i - WIDTH/2) / 12.0f;
                float y = (j - HEIGHT/2) / 6.0f;
                
                // Rotate
                float rx = x * cos(angle) - y * sin(angle);
                float ry = x * sin(angle) + y * cos(angle);
                
                // Teapot body (ellipse)
                if(rx*rx + ry*ry*1.5f < 1.0f && ry > -0.5f) {
                    display[j][i] = '#';
                }
                
                // Spout
                if(rx > 0.8f && rx < 1.3f && abs(ry) < 0.2f && ry > -0.3f) {
                    display[j][i] = '=';
                }
                
                // Handle
                if(rx < -0.8f && rx > -1.2f && abs(ry + 0.1f) < 0.4f && ry > -0.4f) {
                    display[j][i] = '|';
                }
                
                // Lid
                if(rx*rx + (ry-0.5f)*(ry-0.5f) < 0.8f && ry > 0.3f && ry < 0.7f) {
                    display[j][i] = '-';
                }
                
                // Knob
                if(rx*rx + (ry-0.7f)*(ry-0.7f) < 0.1f) {
                    display[j][i] = 'o';
                }
            }
        }
        
        // Convert to string
        for(int j = 0; j < HEIGHT; j++) {
            for(int i = 0; i < WIDTH; i++) {
                result += display[j][i];
            }
            result += '\n';
        }
        
        return result;
    }
}