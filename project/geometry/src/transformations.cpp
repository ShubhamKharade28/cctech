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
    vvd points = X;
    for (auto &v : points) {
        v[0] += dx;
        v[1] += dy;
        v[2] += dz;
    }
    return points;
}

vvd Transformations::rotate(vvd& X, double angle, char axis, vector<double> pivot) {
    vvd points = X;
    double rad = angle * M_PI / 180.0;
    for (auto &v : points) {
        double x = v[0], y = v[1], z = v[2];
        if (axis == 'x') {
            v[1] = y * cos(rad) - z * sin(rad);
            v[2] = y * sin(rad) + z * cos(rad);
        } else if (axis == 'y') {
            v[0] = x * cos(rad) + z * sin(rad);
            v[2] = -x * sin(rad) + z * cos(rad);
        } else if (axis == 'z') {
            v[0] = x * cos(rad) - y * sin(rad);
            v[1] = x * sin(rad) + y * cos(rad);
        }
    }
    return points;
}

vvd Transformations::scale(vvd& X, double scaleFactor, vector<double> pivot) {
    vvd points = X;
    for (auto &v : points) {
        v[0] *= scaleFactor;
        v[1] *= scaleFactor;
        v[2] *= scaleFactor;
    }
    return points;
}
