#ifndef THREED_UTILS_H
#define THREED_UTILS_H

#include <bits/stdc++.h>

#define Vector vector<double>
#define Matrix vector<vector<double>>

class Triangle {
public:
    Vector normal;
    Vector vertex1;
    Vector vertex2;
    Vector vertex3;

    Triangle(Vector normal, Vector vertex1, Vector vertex2, Vector vertex3);
    // Triangle(Vector vertex1, Vector vertex2, Vector vertex3);

    // static Vector computeNormal(Vector v1, Vector v2, Vector v3);
};

#define StlShape vector<Triangle>

class ThreeDUtils {
    public:
        // Read methods
        static StlShape readSTL(const string& filename);
        static StlShape readDAT(const string& filename);
        static StlShape readOBJ(const string& filename);
    
        // Write methods
        static void writeSTL(const string& filename, const StlShape& triangles);
        static void writeDAT(const string& filename, const StlShape& triangles);
        static void writeOBJ(const string& filename, const StlShape& triangles);
    
        // Conversion methods
        static void stlToDat(const string& stlFile, const string& datFile);
        static void datToStl(const string& datFile, const string& stlFile);
        static void stlToObj(const string& stlFile, const string& objFile);
        static void objToStl(const string& objFile, const string& stlFile);
        static void datToObj(const string& datFile, const string& objFile);
        static void objToDat(const string& objFile, const string& datFile);
    };
    
    #endif // THREE_D_UTILS_H
    