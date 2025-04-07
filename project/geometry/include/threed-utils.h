#ifndef THREED_UTILS_H
#define THREED_UTILS_H

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
};

#define StlShape vector<Triangle>

class ThreeDUtils {
public:
    // Read methods
    static StlShape readSTL(string& filename);
    static StlShape readDAT(string& filename);
    static StlShape readOBJ(string& filename);

    // Write methods
    static void writeSTL(string& filename, StlShape& triangles);
    static void writeDAT(string& filename, StlShape& triangles);
    static void writeOBJ(string& filename, StlShape& triangles);

    // Conversion methods
    static void stlToDat(string& stlFile, string& datFile);
    static void datToStl(string& datFile, string& stlFile);
    static void stlToObj(string& stlFile, string& objFile);
    static void objToStl(string& objFile, string& stlFile);
    static void datToObj(string& datFile, string& objFile);
    static void objToDat(string& objFile, string& datFile);

    static Vector computeNormal(Vector v1, Vector v2, Vector v3);

    static void exportSTL(Shape* shape, string filename);
    static void exportOBJ(Shape* shape, string filename);
};

#endif // THREE_D_UTILS_H
    