#include "transformations.h"

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
