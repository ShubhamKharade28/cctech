#include "transformations.h"
#include <cmath>

// Matrix multiplication
vvd multiplyMatrix(const vvd &A, const vvd &B) {
    int r1 = A.size(), c1 = A[0].size(), c2 = B[0].size();
    vvd result(r1, vector<double>(c2, 0));

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Rotation function
vvd rotatePoints(const vvd &X, double angle, vector<double> pivot) {
    if (pivot.empty()) pivot = X[0]; // Default pivot to first point

    double rad = angle * M_PI / 180.0;
    vvd T = {{cos(rad), -sin(rad)}, {sin(rad), cos(rad)}};

    // Shift points relative to pivot
    vvd shiftedX = X;
    for (auto &p : shiftedX) {
        p[0] -= pivot[0];
        p[1] -= pivot[1];
    }

    // Rotate points
    vvd rotatedX = multiplyMatrix(shiftedX, T);

    // Shift back to original position
    for (auto &p : rotatedX) {
        p[0] += pivot[0];
        p[1] += pivot[1];
    }

    return rotatedX;
}

// Scaling function
vvd scalePoints(const vvd &X, double scaleFactor, vector<double> pivot) {
    if (pivot.empty()) pivot = X[0];

    vvd scaledX = X;
    for (auto &p : scaledX) {
        p[0] = pivot[0] + scaleFactor * (p[0] - pivot[0]);
        p[1] = pivot[1] + scaleFactor * (p[1] - pivot[1]);
    }

    return scaledX;
}

// Translation function
vvd translatePoints(const vvd &X, double dx, double dy) {
    vvd translatedX = X;
    for (auto &p : translatedX) {
        p[0] += dx;
        p[1] += dy;
    }
    return translatedX;
}
