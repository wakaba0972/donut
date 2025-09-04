#include<bits/stdc++.h>
#include<math.h>
#ifdef _WIN32
    #include<windows.h>  // for Sleep on Windows
#else
    #include<unistd.h>   // for usleep on Linux
#endif
using namespace std;

#define f float
#define it int16_t
#define rg register

it A = 0, B = 0;
f zbuf[22][40];
char display[22][40];

f sin_table[628];
f cos_table[628];

inline void build_table(){
    for(it i=0; i<628; i+=1){
        sin_table[i] = sin(0.01 * i);
        cos_table[i] = cos(0.01 * i);
    }
}

// Function to clear screen cross-platform
void clear_screen() {
#ifdef _WIN32
    system("CLS");
#else
    cout << "\033[2J\033[1;1H";  // ANSI escape codes to clear screen
#endif
}

inline void update(){
    memset(zbuf, 0, sizeof(zbuf));
    memset(display, ' ', sizeof(display));
    
    A += 7;
    B += 2;
    A %= 628;
    B %= 628;
    
    f sinA = sin_table[(A)], cosA = cos_table[(A)];
    f sinB = sin_table[(B)], cosB = cos_table[(B)];
    
    // Generate cross shape instead of donut
    // We'll create two perpendicular bars that intersect
    for(rg it u=0; u<628; u+=8){
        for(rg it v=0; v<628; v+=8){
            f su = sin_table[u], cu = cos_table[u];
            f sv = sin_table[v], cv = cos_table[v];
            
            // Create two bars: vertical and horizontal
            // Vertical bar (along Y axis)
            f x1 = 0.5 * cu;  // small radius in X
            f y1 = 3 * sv;    // extend along Y
            f z1 = 0.5 * su;  // small radius in Z
            
            // Horizontal bar (along X axis)  
            f x2 = 3 * cv;    // extend along X
            f y2 = 0.5 * su;  // small radius in Y
            f z2 = 0.5 * cu;  // small radius in Z
            
            // Process both bars
            for(int bar = 0; bar < 2; bar++) {
                f x, y, z, L;
                
                if(bar == 0) {
                    // Vertical bar
                    x = x1;
                    y = y1;
                    z = z1;
                    L = abs(cu * sv) + 0.3; // lighting calculation
                } else {
                    // Horizontal bar
                    x = x2;
                    y = y2;
                    z = z2;
                    L = abs(cv * su) + 0.3; // lighting calculation
                }
                
                // Apply rotation matrices
                f rx = cosB*x + sinB*z;
                f ry = sinA*sinB*x + cosA*y - sinA*cosB*z;
                f rz = 7 + cosA*sinB*x - sinA*y + cosA*cosB*z;
                
                f ooz = 1/rz;
                
                it xp = 40/2 + 30*rx*ooz;
                it yp = 22/2 - 15*ry*ooz;
                
                if(L>0.1){
                    if(22 > yp && yp > 0 && xp > 0 && 40 > xp && ooz > zbuf[yp][xp]){
                        zbuf[yp][xp] = ooz;
                        display[yp][xp] = ".,-~:;=!*#$@"[(int8_t)(L*8)];
                    }
                }
            }
        }
    }
    
    clear_screen();
    string s;
    for (rg int8_t j = 0; j < 22; j++) {
        for (rg int8_t i = 0; i < 40; i++) {
          s += display[j][i];
        }
        s += '\n';
    }
    cout << s << '\n';
}

int main() {
    cin.tie(0);
    cout.tie(0);

    build_table();
    
    while(1){
        update();
#ifdef _WIN32
        Sleep(10);
#else
        usleep(50000);  // 50ms delay
#endif
    }
}