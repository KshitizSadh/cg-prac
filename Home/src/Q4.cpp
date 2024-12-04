#include <graphics.h>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Clip boundary values
int x_min = 100, y_min = 100;
int x_max = 400, y_max = 400;

// Function to check if a point is inside the clipping window
bool inside(Point p, int edge) {
    switch (edge) {
        case 1: return p.x >= x_min; // Left edge
        case 2: return p.x <= x_max; // Right edge
        case 3: return p.y >= y_min; // Bottom edge
        case 4: return p.y <= y_max; // Top edge
    }
    return false;
}

// Function to find the intersection point between polygon edge and window boundary
Point intersection(Point p1, Point p2, int edge) {
    Point i;
    float m = (float)(p2.y - p1.y) / (p2.x - p1.x);
    
    switch (edge) {
        case 1: // Left edge
            i.x = x_min;
            i.y = p1.y + (x_min - p1.x) * m;
            break;
        case 2: // Right edge
            i.x = x_max;
            i.y = p1.y + (x_max - p1.x) * m;
            break;
        case 3: // Bottom edge
            i.y = y_min;
            i.x = p1.x + (y_min - p1.y) / m;
            break;
        case 4: // Top edge
            i.y = y_max;
            i.x = p1.x + (y_max - p1.y) / m;
            break;
    }
    return i;
}

// Sutherland-Hodgman clipping algorithm
vector<Point> clipPolygon(vector<Point> polygon, int edge) {
    vector<Point> clippedPolygon;
    int n = polygon.size();
    
    Point s = polygon[n - 1]; // Starting point (previous vertex)
    
    for (int i = 0; i < n; i++) {
        Point p = polygon[i]; // Current vertex
        
        if (inside(p, edge)) {
            if (inside(s, edge)) {
                // Both points are inside, add the current point
                clippedPolygon.push_back(p);
            } else {
                // Previous point is outside, current point is inside, add intersection and current point
                clippedPolygon.push_back(intersection(s, p, edge));
                clippedPolygon.push_back(p);
            }
        } else {
            if (inside(s, edge)) {
                // Previous point is inside, current point is outside, add intersection
                clippedPolygon.push_back(intersection(s, p, edge));
            }
        }
        s = p; // Update previous point
    }
    
    return clippedPolygon;
}

// Function to draw a polygon
void drawPolygon(vector<Point> polygon, int color) {
    int n = polygon.size();
    setcolor(color);
    for (int i = 0; i < n; i++) {
        line(polygon[i].x, polygon[i].y, polygon[(i + 1) % n].x, polygon[(i + 1) % n].y);
    }
}

int main() {
    int gd = DETECT, gm;
    char data[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, data);

    // Original polygon vertices
    vector<Point> polygon = {{150, 150}, {300, 50}, {450, 150}, {350, 250}, {200, 250}};

    // Draw clipping window
    rectangle(x_min, y_min, x_max, y_max);

    // Draw the original polygon in RED
    drawPolygon(polygon, RED);
    getch();

    // Clip polygon against the four edges of the clipping window
    for (int edge = 1; edge <= 4; edge++) {
        polygon = clipPolygon(polygon, edge);
    }

    // Clear the screen and draw the clipped polygon in GREEN
    cleardevice();
    rectangle(x_min, y_min, x_max, y_max);
    drawPolygon(polygon, GREEN);

    getch();
    closegraph();
    return 0;
}
