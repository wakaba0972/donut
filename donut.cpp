#include<bits/stdc++.h>
#include<windows.h>
#include<math.h>
using namespace std;

#define f float
#define it __int16
#define rg register
#define ct cosTHETA
#define st sinTHETA
#define cp cosPHI
#define sp sinPHI

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

inline void update(){
    memset(zbuf, 0, sizeof(zbuf));
    memset(display, ' ', sizeof(display));
    
    A += 7;
    B += 2;
    A %= 628;
    B %= 628;
    
    f sinA = sin_table[(A)], cosA = cos_table[(A)];
    f sinB = sin_table[(B)], cosB = cos_table[(B)];
    
    for(rg it theta=0; theta<628; theta+=4){
        f st = sin_table[(theta)], ct = cos_table[(theta)];
        
        for(rg it phi=0; phi<628; phi+=4){
            f sp = sin_table[(phi)], cp = cos_table[(phi)];
            
            f x = (2+1*ct)*(cosB*cp+sinA*sinB*sp)-1*cosA*sinB*st;
            f y = (2+1*ct)*(sinB*cp-sinA*cosB*sp)+1*cosA*cosB*st;
            f z = 7 + cosA*sp*(2+1*ct)+1*sinA*st;
            f L = cp*ct*sinB-cosA*ct*sp-sinA*st+cosB*(cosA*st-ct*sinA*sp);
            
            f ooz = 1/z;    
            
            it xp = 40/2 + 40*x/(5+z);
            it yp = 22/2 - 40*y/(5+z);
            
            if(L>0){
                if(22 > yp && yp > 0 && xp > 0 && 40 > xp && ooz > zbuf[yp][xp]){
                    zbuf[yp][xp] = ooz;
                    display[yp][xp] = ".,-~:;=!*#$@"[(__int8)(L*8)];
                }
            }
        }
    }
    system("CLS");
    string s;
    for (rg __int8 j = 0; j < 22; j++) {
        for (rg __int8 i = 0; i < 40; i++) {
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
        Sleep(10);
    }
}