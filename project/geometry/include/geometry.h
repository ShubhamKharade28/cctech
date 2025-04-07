#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <bits/stdc++.h>
using namespace std;

#include "gnuplot-utils.h"
#include "transformations.h"
#include "threed-utils.h"

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
protected:
    double x=0, y=0, z=0;
public:
    virtual vvd computePoints() = 0;
    virtual StlShape computeTriangles() = 0;

    virtual void draw();
    vvd getDrawable();
    virtual void input() = 0;

    Vector getCoords() {
        return {x,y,z};
    }

    void setCoords(double x=0, double y=0, double z=0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    virtual ~Shape() {};
};

class Rectangle: public Shape {
    double l,b;
public:    
    Rectangle(double l=1, double b=1);
    vvd computePoints() override;
    void input();

    StlShape computeTriangles() override {return {};};
};

class Cuboid: public Shape {
    double l, b, h;
public:
    Cuboid(double l=1, double b=1, double h=1);
    vvd computePoints() override;
    void input() override;

    StlShape computeTriangles() override;
};

class Cube : public Cuboid {
public:
    double side;
    Cube(double side = 1);
};

class Circle: public Shape {
    double r;
public:
    Circle(double r = 1);
    void input() ;
    vvd computePoints() override;
    StlShape computeTriangles() override {return {};};
};

class Sphere: public Shape{
public:
    double r;
    Sphere(double r=1);
    vvd computePoints() override;
    void input() override;
    StlShape computeTriangles() override {return {};};
};

class Cylinder: public Shape {
    double r, h;
public: 
    Cylinder(double r=1,  double h=10);
    vvd computePoints() override;
    void input() override;

    StlShape computeTriangles() override;
};

class Polyline: public Shape{
public:
    vvd points;
    Polyline(vvd& pts) : points(pts) {}
    vvd computePoints() override { return points; }
    StlShape computeTriangles() override {return {};};
};

class BezierCurve: public Shape{
public:
    vvd controlPoints;
    BezierCurve(vvd& points);
    vvd computePoints() override { return controlPoints; }
    void draw();

    StlShape computeTriangles() override {return {};};
};
    

#endif