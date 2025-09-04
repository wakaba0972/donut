#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>
#include <string>

namespace ASCII3D {
    
    class DonutRenderer {
    private:
        static constexpr int WIDTH = 40;
        static constexpr int HEIGHT = 22;
        
        int16_t A, B;
        float zbuf[HEIGHT][WIDTH];
        char display[HEIGHT][WIDTH];
        float sin_table[628];
        float cos_table[628];
        
        void buildTable();
        
    public:
        DonutRenderer();
        void update();
        std::string render();
        void reset();
    };
    
    // Shape types for future extension
    enum class ShapeType {
        DONUT,
        CUBE,
        SPHERE,
        TEAPOT
    };
    
    class Shape3D {
    public:
        virtual ~Shape3D() = default;
        virtual std::string render() = 0;
        virtual void update() = 0;
    };
}

#endif