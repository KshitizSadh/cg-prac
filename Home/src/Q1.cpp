#include <iostream>
#include <graphics.h>
using namespace std;

void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p = 2 * dy - dx;
    int x = x1, y = y1;
    
    while (x <= x2) {
        putpixel(x, y, WHITE);
        if (p >= 0) {
            y++;
            p += 2 * dy - 2 * dx;
        } else {
            p += 2 * dy;
        }
        x++;
    }
}

int main() {
    int gd = DETECT, gm;
    char data[] = "C:\\MinGW\\lib\\libbgi.a";
    
    initgraph(&gd, &gm, data);
    
    int x1 = 100, y1 = 100, x2 = 200, y2 = 150;
    bresenhamLine(x1, y1, x2, y2);
    
    getch();
    closegraph();
    return 0;
}
