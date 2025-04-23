#include "transformations.h"

QMatrix4x4 Transformations::getTransformationMatrix(vector<double> translation, vector<double> rotation, double scale) {
    QMatrix4x4 transform;
    transform.setToIdentity();

    transform.scale(scale);

    // transform.translate(-center[0], -center[1], -center[2]); // Translate to center
    transform.rotate(rotation[0], 1.0f, 0.0f, 0.0f);
    transform.rotate(rotation[1], 0.0f, 1.0f, 0.0f);
    transform.rotate(rotation[2], 0.0f, 0.0f, 1.0f);
    // transform.translate(center[0], center[1], center[2]); // Translate back to original position

    transform.translate(translation[0], translation[1], translation[2]); // Apply translation
    return transform;
}

Matrix Transformations::applyTransformations(Matrix& X, vector<double> translation, vector<double> rotation, double scale) {
    QMatrix4x4 transform = getTransformationMatrix(translation, rotation, scale);
    Matrix X_transformed(X.size(), vector<double>(X[0].size(), 0));
    for(int i = 0; i < X.size(); i++) {
        for(int j = 0; j < X[0].size(); j++) {
            QVector4D point(X[i][j], X[i][j], X[i][j], 1.0);
            point = transform * point;
            X_transformed[i][j] = point.x();
        }
    }
    return X_transformed;
}

StlShape Transformations::applyTransformations(StlShape& X, vector<double> translation, vector<double> rotation, double scale) {
    QMatrix4x4 transform = getTransformationMatrix(translation, rotation, scale);
    StlShape X_transformed;
    for (auto& tri : X) {
        Triangle transformedTri;
        QVector4D v1(tri.vertex1[0], tri.vertex1[1], tri.vertex1[2], 1.0);
        QVector4D v2(tri.vertex2[0], tri.vertex2[1], tri.vertex2[2], 1.0);
        QVector4D v3(tri.vertex3[0], tri.vertex3[1], tri.vertex3[2], 1.0);

        v1 = transform * v1;
        v2 = transform * v2;
        v3 = transform * v3;

        transformedTri.vertex1 = {v1.x(), v1.y(), v1.z()};
        transformedTri.vertex2 = {v2.x(), v2.y(), v2.z()};
        transformedTri.vertex3 = {v3.x(), v3.y(), v3.z()};

        X_transformed.push_back(transformedTri);
    }
    return X_transformed;
}