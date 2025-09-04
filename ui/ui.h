#ifndef UI_H
#define UI_H

#include "../core/renderer.h"
#include "../log/logger.h"
#include <memory>

namespace ASCII3D {
    
    class UserInterface {
    private:
        std::unique_ptr<DonutRenderer> renderer;
        ShapeType currentShape;
        bool running;
        
        void clearScreen();
        void displayMenu();
        void handleInput();
        void displayShapeInfo();
        
    public:
        UserInterface();
        ~UserInterface() = default;
        
        void run();
        void stop();
        void setShape(ShapeType shape);
        ShapeType getCurrentShape() const;
    };
}

#endif