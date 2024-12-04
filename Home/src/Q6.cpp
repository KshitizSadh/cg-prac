#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void applyTransformation(float matrix[3][3], int &x, int &y) {
    int xNew = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2];
    int yNew = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2];
    x = xNew;
    y = yNew;
}

void drawTransformedObject(float matrix[3][3]) {
    int x1 = 100, y1 = 100;
    int x2 = 200, y2 = 100;
    int x3 = 200, y3 = 200;
    int x4 = 100, y4 = 200;

    applyTransformation(matrix, x1, y1);
    applyTransformation(matrix, x2, y2);
    applyTransformation(matrix, x3, y3);
    applyTransformation(matrix, x4, y4);

    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x4, y4);
    line(x4, y4, x1, y1);
}

void multiplyMatrices(float result[3][3], float mat1[3][3], float mat2[3][3]) {
    float temp[3][3] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                temp[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    // Copy result to the result matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = temp[i][j];
        }
    }
}

void transformAndDraw(float transformationMatrix[3][3]) {
    // Draw the original object
    setcolor(WHITE);
    int x1 = 100, y1 = 100, x2 = 200, y2 = 100, x3 = 200, y3 = 200, x4 = 100, y4 = 200;
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x4, y4);
    line(x4, y4, x1, y1);

    // Apply the combined transformation and draw the transformed object
    setcolor(YELLOW);
    drawTransformedObject(transformationMatrix);
}

int main() {
    int gd = DETECT, gm;
    char data[] = "C:\\MinGW\\lib\\libbgi.a"; // Path to the BGI library, adjust as per your system
    initgraph(&gd, &gm, data);

    // Identity matrix (no transformation)
    float transformationMatrix[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    // Translation matrix
    float translationMatrix[3][3] = {
        {1, 0, 50},
        {0, 1, 50},
        {0, 0, 1}
    };

    // Scaling matrix
    float scaleMatrix[3][3] = {
        {0.5, 0, 0},
        {0, 0.5, 0},
        {0, 0, 1}
    };

    // Rotation matrix (45 degrees)
    float angle = 45 * M_PI / 180.0; // Convert degrees to radians
    float rotationMatrix[3][3] = {
        {cos(angle), -sin(angle), 0},
        {sin(angle), cos(angle), 0},
        {0, 0, 1}
    };

    // Combine transformations: First translate, then scale, then rotate
    multiplyMatrices(transformationMatrix, translationMatrix, transformationMatrix); // Translation
    multiplyMatrices(transformationMatrix, scaleMatrix, transformationMatrix);       // Scaling
    multiplyMatrices(transformationMatrix, rotationMatrix, transformationMatrix);     // Rotation

    // Apply combined transformation and draw the object
    transformAndDraw(transformationMatrix);

    getch();
    closegraph();
    return 0;
}
