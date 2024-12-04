#include <graphics.h>
#include <iostream>
using namespace std;

void drawHermiteCurve(int x0, int y0, int x1, int y1, int rx0, int ry0, int rx1, int ry1) {
    float t, h00, h10, h01, h11;
    int x, y;

    for (t = 0.0; t <= 1.0; t += 0.001) {
        h00 = 2*t*t*t - 3*t*t + 1;
        h10 = t*t*t - 2*t*t + t;
        h01 = -2*t*t*t + 3*t*t;
        h11 = t*t*t - t*t;

        x = h00*x0 + h10*rx0 + h01*x1 + h11*rx1;
        y = h00*y0 + h10*ry0 + h01*y1 + h11*ry1;

        putpixel(x, y, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    char data[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, data);

    int x0 = 100, y0 = 200, x1 = 300, y1 = 300;
    int rx0 = 100, ry0 = 100, rx1 = 200, ry1 = 150;

    drawHermiteCurve(x0, y0, x1, y1, rx0, ry0, rx1, ry1);

    getch();
    closegraph();
    return 0;
}
