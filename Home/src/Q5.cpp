#include <iostream>
#include <graphics.h>
using namespace std;

struct Point {
    int x, y;
};

void scanLine(Point polygon[], int n) {
    int ymin = polygon[0].y, ymax = polygon[0].y;
    for (int i = 1; i < n; i++) {
        if (polygon[i].y < ymin) ymin = polygon[i].y;
        if (polygon[i].y > ymax) ymax = polygon[i].y;
    }

    for (int y = ymin; y <= ymax; y++) {
        int xIntersections[20], k = 0;

        for (int i = 0; i < n; i++) {
            int x1 = polygon[i].x, y1 = polygon[i].y;
            int x2 = polygon[(i + 1) % n].x, y2 = polygon[(i + 1) % n].y;

            if (y1 != y2) {
                if (y >= min(y1, y2) && y <= max(y1, y2)) {
                    int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                    xIntersections[k++] = x;
                }
            }
        }

        for (int i = 0; i < k - 1; i += 2) {
            line(xIntersections[i], y, xIntersections[i + 1], y);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    char data[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, data);


    Point polygon[] = {{200, 100}, {300, 200}, {250, 300}, {150, 300}, {100, 200}};
    int n = sizeof(polygon) / sizeof(polygon[0]);

    setcolor(WHITE);
    for (int i = 0; i < n; i++) {
        line(polygon[i].x, polygon[i].y, polygon[(i + 1) % n].x, polygon[(i + 1) % n].y);
    }

    scanLine(polygon, n);

    getch();
    closegraph();
    return 0;
}
