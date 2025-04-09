#include "transformations.h"

Matrix Transformations::translate(Matrix& X, double dx, double dy, double dz) {
    Matrix points = X;
    for (auto &v : points) {
        v[0] += dx;
        v[1] += dy;
        v[2] += dz;
    }
    return points;
}

Matrix Transformations::rotate(Matrix& X, double angle, char axis, vector<double> pivot) {
    Matrix points = X;
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

Matrix Transformations::scale(Matrix& X, double scaleFactor, vector<double> pivot) {
    /* TODO: if pivot is not origin, 
        implement additional steps like,
        translating first to origin, then after scaling, retranslate it to its position 
    */
    Matrix points = X;
    for (auto &v : points) {
        v[0] *= scaleFactor;
        v[1] *= scaleFactor;
        v[2] *= scaleFactor;
    }
    return points;
}

Triangle Transformations::translateTriangle(const Triangle& tri, Vector& t) {
    Matrix points = {
        {tri.vertex1[0], tri.vertex1[1], tri.vertex1[2]},
        {tri.vertex2[0], tri.vertex2[1], tri.vertex2[2]},
        {tri.vertex3[0], tri.vertex3[1], tri.vertex3[2]}
    };

    Matrix result = translate(points, t[0], t[1], t[2]);
    return Triangle(result[0], result[1], result[2]);
}

Triangle Transformations::scaleTriangle(const Triangle& tri, double scaleFactor, const Vector& pivot) {
    Matrix points = {
        {tri.vertex1[0], tri.vertex1[1], tri.vertex1[2]},
        {tri.vertex2[0], tri.vertex2[1], tri.vertex2[2]},
        {tri.vertex3[0], tri.vertex3[1], tri.vertex3[2]}
    };

    Matrix result = scale(points, scaleFactor, pivot);
    return Triangle(result[0], result[1], result[2]); 
}

Triangle Transformations::rotateTriangle(const Triangle& tri, const Vector& rotations, const Vector& pivot) {
    Matrix points = {
        {tri.vertex1[0], tri.vertex1[1], tri.vertex1[2]},
        {tri.vertex2[0], tri.vertex2[1], tri.vertex2[2]},
        {tri.vertex3[0], tri.vertex3[1], tri.vertex3[2]}
    };

    Matrix result = points;
    if (rotations[0] != 0) result = rotate(result, rotations[0], 'x', pivot);
    if (rotations[1] != 0) result = rotate(result, rotations[1], 'y', pivot);
    if (rotations[2] != 0) result = rotate(result, rotations[2], 'z', pivot);

    return Triangle(result[0], result[1], result[2]);
}

StlShape Transformations::translateShape(const StlShape& shape, Vector& t) {
    StlShape result;
    for (const auto& tri : shape) {
        result.push_back(translateTriangle(tri, t));
    }
    return result;
}

StlShape Transformations::scaleShape(const StlShape& shape, double scaleFactor, const Vector& pivot) {
    StlShape result;
    for (const auto& tri : shape) {
        result.push_back(scaleTriangle(tri, scaleFactor, pivot));
    }
    return result;
}

StlShape Transformations::rotateShape(const StlShape& shape, const Vector& rotations, const Vector& pivot) {
    StlShape result;
    for (const auto& tri : shape) {
        result.push_back(rotateTriangle(tri, rotations, pivot));
    }
    return result;
}
