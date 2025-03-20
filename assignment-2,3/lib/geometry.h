#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <bits/stdc++.h>
#include "gnuplot-utils.h"
using namespace std;

class Point {
public:
    double x, y;
    Point();
    Point(double x, double y);
    pair<double, double> toPair();
};

class Point3D : public Point {
public:
    double z;
    Point3D();
    Point3D(double x, double y, double z);
    tuple<double, double, double> toTuple() const;
};

template <typename T>
class Line {
public:
    T start, end;
    Line(T s, T e);
    void draw();
};

#endif
