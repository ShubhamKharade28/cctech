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
    virtual vector<double> toVector() { return {x, y}; }
};

class Point3D : public Point {
public:
    double z;
    Point3D(): Point(0,0) {};
    Point3D(double x=0, double y=0, double z=0): Point(x,y), z(z) {}
    vector<double> toVector() override { return {x, y, z}; }
};

template <typename T>
class Line {
public:
    T start, end;
    Line(T s, T e): start(s), end(e) {};
    void draw();
};

class Shape {
public:
    virtual vvd getDrawable() = 0;
    virtual void draw() = 0;
    virtual ~Shape() {};

    double degToRad(double degrees) {
        return degrees * M_PI / 180.0;
    }

    double radToDeg(double radians) {
        return radians * 180.0 / M_PI;
    }
};

class Rectangle: public Shape {
public:
    double l,b;
    double x,y,z;
    
    Rectangle(double x=0, double y=0, double z=0, double l=1, double b=1);
    void draw() override;
    vvd getDrawable() override;
    void input();
    Rectangle rotate90();
};

class Cuboid: public Shape {
public:
    double x, y, z;
    double l, b, h;
    double rotationX, rotationY, rotationZ;

    Cuboid(double x = 0, double y = 0, double z = 0, double l = 1, double b = 1, double h = 1);
    void draw() override;
    vvd getDrawable() override;
    void setRotation(double rotX_deg, double rotY_deg, double rotZ_deg);  
};

class Cube : public Cuboid {
public:
    double side;
    Cube(double side = 1, double x = 0, double y = 0, double z = 0);
};

class Circle: public Shape {
public:
    double x, y, z, r;
    Circle(double x = 0, double y = 0, double z = 0, double r = 1);
    void draw() override;
    void input() ;
    vvd getDrawable() override;
};

class Sphere: public Shape{
public:
    double x,y,z,r;
    Sphere(double x, double y, double z, double r);
    void draw() override;
    vvd getDrawable() override;
};

class Cylinder: public Shape {
public:
    double x, y, z; 
    double r, h;
    Cylinder(double x, double y, double z, double r, double h)
        : x(x), y(y), z(z), r(r), h(h) {}

    void draw() override;
    vvd getDrawable() override;
};

class Polyline: public Shape{
public:
    vvd points;
    Polyline(vvd& pts) : points(pts) {}
    vvd getDrawable() override { return points; }
    void draw() override;
};

class BezierCurve: public Shape{
public:
    vvd controlPoints;
    BezierCurve(vvd& points);
    vvd getDrawable() override { return controlPoints; }
    void draw() override;
};
    

#endif