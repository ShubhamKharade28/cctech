#pragma once

#include <bits/stdc++.h>
using namespace std; 

#define Vector vector<double>
#define Matrix vector<vector<double>>

#include <QDebug>

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
    Triangle() {
        normal = {0, 0, 0};
        vertex1 = {0, 0, 0};
        vertex2 = {0, 0, 0};
        vertex3 = {0, 0, 0};
    }

    Vector getNormal();

    static Vector computeNormal(Vector v1, Vector v2, Vector v3) {
        Vector edge1 = substract(v2, v1);
        Vector edge2 = substract(v3, v1);
        return normalize(cross(edge1, edge2));
    }
};

#define StlShape vector<Triangle>
using Line = pair<Vector, Vector>;


double dot(Vector a, Vector b);
optional<Line> clipTriangleToLine(const Triangle& tri, const Vector& p0, const Vector& dir);
optional<Line> getIntersection(Triangle& t1, Triangle& t2);
optional<Line> segmentOverlap(Line seg1, Line seg2);
optional<Line> getIntersection(Triangle& t1, Triangle& t2);
vector<Line> getIntersections(StlShape& shape1, StlShape& shape2);

/*
// Sakshi's code
bool trianglesCoplanar(Triangle& t1, Triangle& t2);
bool triangleTriangleIntersectionSegment(const Triangle& t1, const Triangle& t2, Vector& segA, Vector& segB);
    */