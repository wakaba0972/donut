# 天啊!是一個十字架，他會旋轉!

### 原本是甜甜圈，現在變成了旋轉的十字架! 因為這是用z-buffer繪製的，同樣的方法，可以試試用向量把其他形狀的面繪製出來，像是cube，甚至茶壺!?

## Spinning Cross (Originally Donut)

This is a 3D ASCII art program that renders a rotating cross shape using z-buffer techniques. The program was originally designed to display a spinning donut (torus) but has been transformed to show a cross shape instead.

### Features
- 3D rotating cross rendered in ASCII
- Cross-platform compatibility (Windows and Linux)
- Real-time rotation animation
- Z-buffer depth calculation for proper 3D rendering

### Compilation
```bash
# On Linux/Unix:
g++ donut.cpp -o cross -lm

# On Windows:
g++ donut.cpp -o cross.exe
```

### Usage
```bash
./cross
```
Press Ctrl+C to exit.
