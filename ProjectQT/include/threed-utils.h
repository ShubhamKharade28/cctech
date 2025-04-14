#pragma once

#include <bits/stdc++.h>
using namespace std; 

class Shape;

#define Vector vector<double>
#define Matrix vector<vector<double>>

Vector substract(Vector a, Vector b);
Vector cross(Vector a, Vector b);
double magnitude(Vector v);
Vector normalize(Vector v);

class Triangle {
public:
    Vector normal;
    Vector vertex1;
    Vector vertex2;
    Vector vertex3;

    Triangle(Vector normal, Vector vertex1, Vector vertex2, Vector vertex3);
    Triangle(Vector v1, Vector v2, Vector v3);

    Vector getNormal();

    static Vector computeNormal(Vector v1, Vector v2, Vector v3);
};

#define StlShape vector<Triangle>