#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <bits/stdc++.h>
using namespace std;

#include "gnuplot-utils.h"

class Point {
public:
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
    pair<double, double> toPair() { return {x, y}; }
};

class Point3D : public Point {
public:
    double z;
    Point3D();
    Point3D(double x=0, double y=0, double z=0): Point(x,y), z(z) {}
    tuple<double, double, double> toTuple() { return {x, y, z}; }
};

template <typename T>
class Line {
public:
    T start, end;
    Line(T s, T e): start(s), end(e) {};
    void draw();
};

class Rectangle {
public:
    double l,b;
    double x,y;
    
    Rectangle(double x=0, double y=0, double l=1, double b=1): l(l), b(b), x(x), y(y) {}
    void draw();
    void input();
};

class Cuboid {
public:
    double l, b, h;
    double x, y, z;

    Cuboid(double x = 0, double y = 0, double z = 0, double l = 1, double b = 1, double h = 1)
        : l(l), b(b), h(h), x(x), y(y), z(z) {}  

    void draw();
};

class Cube : public Cuboid {
public:
    double side;

    Cube(double side = 1, double x = 0, double y = 0, double z = 0)
        : Cuboid(x, y, z, side, side, side), side(side) {}
};

class Circle {
public:
    double x, y, z, r;
    bool is3D;

    Circle(double x = 0, double y = 0, double z = 0, double r = 1, bool is3D = false)
        : x(x), y(y), z(z), r(r), is3D(is3D) {}

    void draw();
    void input();
};
    

#endif
