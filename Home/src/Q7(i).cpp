#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

// Function to apply 3D transformations
void apply3DTransformation(float matrix[4][4], int &x, int &y, int &z) {
    int xNew = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
    int yNew = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
    int zNew = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3];
    x = xNew;
    y = yNew;
    z = zNew;
}

// Function to project 3D points onto a 2D plane (Parallel Projection)
void parallelProjection(int x, int y, int z, int &x2D, int &y2D) {
    // In parallel projection, the z-coordinate is ignored
    x2D = x;
    y2D = y;
}

// Function to multiply two 4x4 matrices
void multiplyMatrices(float result[4][4], float mat1[4][4], float mat2[4][4]) {
    float temp[4][4] = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                temp[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    // Copy result to the result matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = temp[i][j];
        }
    }
}

// Draw the transformed and projected 3D object
void drawTransformed3DObject(float matrix[4][4]) {
    // Cube vertices
    int x1 = 100, y1 = 100, z1 = 100;
    int x2 = 200, y2 = 100, z2 = 100;
    int x3 = 200, y3 = 200, z3 = 100;
    int x4 = 100, y4 = 200, z4 = 100;
    int x5 = 100, y5 = 100, z5 = 200;
    int x6 = 200, y6 = 100, z6 = 200;
    int x7 = 200, y7 = 200, z7 = 200;
    int x8 = 100, y8 = 200, z8 = 200;

    // Apply transformation
    apply3DTransformation(matrix, x1, y1, z1);
    apply3DTransformation(matrix, x2, y2, z2);
    apply3DTransformation(matrix, x3, y3, z3);
    apply3DTransformation(matrix, x4, y4, z4);
    apply3DTransformation(matrix, x5, y5, z5);
    apply3DTransformation(matrix, x6, y6, z6);
    apply3DTransformation(matrix, x7, y7, z7);
    apply3DTransformation(matrix, x8, y8, z8);

    // Project 3D points to 2D (Parallel Projection)
    int x1_2D, y1_2D, x2_2D, y2_2D, x3_2D, y3_2D, x4_2D, y4_2D;
    int x5_2D, y5_2D, x6_2D, y6_2D, x7_2D, y7_2D, x8_2D, y8_2D;
    parallelProjection(x1, y1, z1, x1_2D, y1_2D);
    parallelProjection(x2, y2, z2, x2_2D, y2_2D);
    parallelProjection(x3, y3, z3, x3_2D, y3_2D);
    parallelProjection(x4, y4, z4, x4_2D, y4_2D);
    parallelProjection(x5, y5, z5, x5_2D, y5_2D);
    parallelProjection(x6, y6, z6, x6_2D, y6_2D);
    parallelProjection(x7, y7, z7, x7_2D, y7_2D);
    parallelProjection(x8, y8, z8, x8_2D, y8_2D);

    // Draw cube edges
    setcolor(WHITE);
    line(x1_2D, y1_2D, x2_2D, y2_2D);
    line(x2_2D, y2_2D, x3_2D, y3_2D);
    line(x3_2D, y3_2D, x4_2D, y4_2D);
    line(x4_2D, y4_2D, x1_2D, y1_2D);

    line(x5_2D, y5_2D, x6_2D, y6_2D);
    line(x6_2D, y6_2D, x7_2D, y7_2D);
    line(x7_2D, y7_2D, x8_2D, y8_2D);
    line(x8_2D, y8_2D, x5_2D, y5_2D);

    line(x1_2D, y1_2D, x5_2D, y5_2D);
    line(x2_2D, y2_2D, x6_2D, y6_2D);
    line(x3_2D, y3_2D, x7_2D, y7_2D);
    line(x4_2D, y4_2D, x8_2D, y8_2D);
}

// 3D Translation
void translate3D(int tx, int ty, int tz, float transformationMatrix[4][4]) {
    float translationMatrix[4][4] = {
        {1, 0, 0, static_cast<float>(tx)},
        {0, 1, 0, static_cast<float>(ty)},
        {0, 0, 1, static_cast<float>(tz)},
        {0, 0, 0, 1}
    };
    multiplyMatrices(transformationMatrix, translationMatrix, transformationMatrix);
}

// 3D Scaling
void scale3D(float sx, float sy, float sz, float transformationMatrix[4][4]) {
    float scaleMatrix[4][4] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}
    };
    multiplyMatrices(transformationMatrix, scaleMatrix, transformationMatrix);
}

// 3D Rotation around Z-axis
void rotate3D(float angle, float transformationMatrix[4][4]) {
    float rad = angle * M_PI / 180.0;
    float rotationMatrix[4][4] = {
        {cos(rad), -sin(rad), 0, 0},
        {sin(rad), cos(rad), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    multiplyMatrices(transformationMatrix, rotationMatrix, transformationMatrix);
}

int main() {
    int gd = DETECT, gm;
    char data[] = "C:\\MinGW\\lib\\libbgi.a";
    initgraph(&gd, &gm, data);

    // Identity matrix (no transformation)
    float transformationMatrix[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Apply translation, scaling, and rotation
    translate3D(50, 50, 50, transformationMatrix);
    scale3D(1.5, 1.5, 1.5, transformationMatrix);
    rotate3D(45, transformationMatrix);

    // Draw the transformed object
    drawTransformed3DObject(transformationMatrix);

    getch();
    closegraph();
    return 0;
}
