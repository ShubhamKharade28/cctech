#include "transformations.h"

vvd Transformations::toHomogeneous(vvd& points) {
    vvd homogeneousPoints;
    for (auto& point : points) {
        if (point.size() == 3) {
            homogeneousPoints.push_back({point[0], point[1], point[2], 1.0});
        } else {
            throw std::invalid_argument("Points must have exactly 3 coordinates (x, y, z)");
        }
    }
    return homogeneousPoints;
}

vvd Transformations::toCartesian(vvd& homogeneousX) {
    vvd cartesianX;
    for (const auto& point : homogeneousX) {
        if (point.size() < 4 || point[3] == 0) {
            throw std::runtime_error("Invalid homogeneous coordinate: w must be nonzero.");
        }
        cartesianX.push_back({point[0] / point[3], point[1] / point[3], point[2] / point[3]});
    }
    return cartesianX;
}

vvd Transformations::multiplyMatrix(vvd &A, vvd &B) {
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

vvd Transformations::translate(vvd& X, double dx, double dy, double dz) {
    vvd homogeneousX = toHomogeneous(X);

    // translation matrix
    vvd T = {
        {1, 0, 0, dx},
        {0, 1, 0, dy},
        {0, 0, 1, dz},
        {0, 0, 0, 1}
    };

    vvd transformed = multiplyMatrix(homogeneousX, T);
    vvd translatedX = toCartesian(transformed);

    return translatedX;
}

vvd Transformations::rotate(vvd& X, double angle, char axis, vector<double> pivot) {
    if(X.empty()) return {};
    if(pivot.empty()) pivot = X[0];

    // double cx = pivot[0], cy = pivot[1], cz = pivot[2];
    // vvd translatedX = translate(X, -cx, -cy, -cz);

    vvd translatedX = X;

    double theta = angle * M_PI / 180.0;
    vvd R; // rotation matrix
    if (axis == 'x') {
        R = {
            {1, 0, 0, 0},
            {0, cos(theta), -sin(theta), 0},
            {0, sin(theta), cos(theta), 0},
            {0, 0, 0, 1}
        };
    } else if (axis == 'y') {
        R = {
            {cos(theta), 0, sin(theta), 0},
            {0, 1, 0, 0},
            {-sin(theta), 0, cos(theta), 0},
            {0, 0, 0, 1}
        };
    } else if (axis == 'z') {
        R = {
            {cos(theta), -sin(theta), 0, 0},
            {sin(theta), cos(theta), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
    }

    vvd homogeneousX = toHomogeneous(translatedX);
    vvd rotatedX = multiplyMatrix(homogeneousX, R);

    rotatedX = toCartesian(rotatedX);
    // rotatedX = translate(rotatedX, cx, cy, cz);
    return rotatedX;
}

vvd Transformations::scale(vvd& X, double scaleFactor, vector<double> pivot) {
    if (pivot.empty()) pivot = X[0];

    vvd scaledX = X;
    for (auto &p : scaledX) {
        p[0] = pivot[0] + scaleFactor * (p[0] - pivot[0]);
        p[1] = pivot[1] + scaleFactor * (p[1] - pivot[1]);
        p[2] = pivot[2] + scaleFactor * (p[2] - pivot[2]);
    }

    return scaledX;
}
