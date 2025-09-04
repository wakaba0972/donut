#include "renderer.h"
#include <cmath>
#include <cstring>
#include <iostream>

namespace ASCII3D {
    
    DonutRenderer::DonutRenderer() : A(0), B(0) {
        buildTable();
        reset();
    }
    
    void DonutRenderer::buildTable() {
        for(int16_t i = 0; i < 628; i += 1) {
            sin_table[i] = sin(0.01 * i);
            cos_table[i] = cos(0.01 * i);
        }
    }
    
    void DonutRenderer::reset() {
        memset(zbuf, 0, sizeof(zbuf));
        memset(display, ' ', sizeof(display));
    }
    
    void DonutRenderer::update() {
        reset();
        
        A += 7;
        B += 2;
        A %= 628;
        B %= 628;
        
        float sinA = sin_table[A], cosA = cos_table[A];
        float sinB = sin_table[B], cosB = cos_table[B];
        
        for(int16_t theta = 0; theta < 628; theta += 4) {
            float st = sin_table[theta], ct = cos_table[theta];
            
            for(int16_t phi = 0; phi < 628; phi += 4) {
                float sp = sin_table[phi], cp = cos_table[phi];
                
                float x = (2 + 1 * ct) * (cosB * cp + sinA * sinB * sp) - 1 * cosA * sinB * st;
                float y = (2 + 1 * ct) * (sinB * cp - sinA * cosB * sp) + 1 * cosA * cosB * st;
                float z = 7 + cosA * sp * (2 + 1 * ct) + 1 * sinA * st;
                float L = cp * ct * sinB - cosA * ct * sp - sinA * st + cosB * (cosA * st - ct * sinA * sp);
                
                float ooz = 1 / z;
                
                int16_t xp = WIDTH / 2 + WIDTH * x / (5 + z);
                int16_t yp = HEIGHT / 2 - WIDTH * y / (5 + z);
                
                if(L > 0) {
                    if(HEIGHT > yp && yp > 0 && xp > 0 && WIDTH > xp && ooz > zbuf[yp][xp]) {
                        zbuf[yp][xp] = ooz;
                        display[yp][xp] = ".,-~:;=!*#$@"[(int8_t)(L * 8)];
                    }
                }
            }
        }
    }
    
    std::string DonutRenderer::render() {
        std::string result;
        for(int8_t j = 0; j < HEIGHT; j++) {
            for(int8_t i = 0; i < WIDTH; i++) {
                result += display[j][i];
            }
            result += '\n';
        }
        return result;
    }
}