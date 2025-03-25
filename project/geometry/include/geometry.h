#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <bits/stdc++.h>
using namespace std;

#include "gnuplot-utils.h"
#include "transformations.h"

#define vvd vector<vector<double>>
#define pi pair<int, int>

class Point {
public:
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
    pair<double, double> toPair() { return {x, y}; }
};

class Point3D : public Point {
public:
    double z;
    Point3D(): Point(0,0) {};
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
    
    Rectangle(double x=0, double y=0, double l=1, double b=1);
    void draw();
    void input();
    Rectangle rotate90();
};

class Cuboid {
public:
    double l, b, h;
    double x, y, z;

    Cuboid(double x = 0, double y = 0, double z = 0, double l = 1, double b = 1, double h = 1);
    void draw();
};

class Cube : public Cuboid {
public:
    double side;
    Cube(double side = 1, double x = 0, double y = 0, double z = 0);
};

class Circle {
public:
    double x, y, z, r;
    bool is3D;

    Circle(double x = 0, double y = 0, double z = 0, double r = 1, bool is3D = false);
    void draw();
    void input();
};

class Sphere {
public:
    double x,y,z,r;
    Sphere(double x, double y, double z, double r);
    void draw();
};

class Cylinder {
public:
    double x, y, z; 
    double r, h;
    Cylinder(double x, double y, double z, double r, double h)
        : x(x), y(y), z(z), r(r), h(h) {}

    void draw();
};
    

#endif