#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <bits/stdc++.h>
using namespace std;

#include "threed-utils.h"

// #define Matrix vector<vector<double>>

class Transformations {
public:
    Matrix translate(Matrix& X, double dx, double dy, double dz); 
    Matrix rotate(Matrix& X, double angle, char axis, vector<double> pivot = {}); 
    Matrix scale(Matrix& X, double scaleFactor, vector<double> pivot = {});

    Triangle translateTriangle(const Triangle& tri, Vector& t);
    Triangle scaleTriangle(const Triangle& tri, double scaleFactor, const Vector& pivot = {});
    Triangle rotateTriangle(const Triangle& tri, const Vector& rotations, const Vector& pivot = {});

    StlShape translateShape(const StlShape& shape, Vector& t);
    StlShape scaleShape(const StlShape& shape, double scaleFactor, const Vector& pivot = {});
    StlShape rotateShape(const StlShape& shape, const Vector& rotations, const Vector& pivot = {});
};

#endif
