#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "shape.h"
#include "threed-utils.h"

class Rectangle: public Shape {
    double l,b;
public:    
    Rectangle(double l=1, double b=1);
    Matrix computePoints() override;
    void input();

    StlShape computeTriangles() override {return {};};
};

class Cuboid: public Shape {
    double l, b, h;
public:
    Cuboid(double l=1, double b=1, double h=1);
    Matrix computePoints() override;
    void input() override;

    StlShape computeTriangles() override;
    string getType() override { return "cuboid"; };
};

class Cube : public Cuboid {
public:
    double side;
    Cube(double side = 1);
    string getType() override { return "cube"; }
};

class Circle: public Shape {
    double r;
public:
    Circle(double r = 1);
    void input();
    Matrix computePoints() override;
    StlShape computeTriangles() override {return {};};
    string getType() override { return "circle"; }
};

class Sphere: public Shape{
public:
    double r;
    Sphere(double r=1);
    Matrix computePoints() override;
    void input() override;
    StlShape computeTriangles() override {return {};};
    string getType() override { return "sphere"; }
};

class Cylinder: public Shape {
    double r, h;
public: 
    Cylinder(double r=1,  double h=10);
    Matrix computePoints() override;
    void input() override;

    StlShape computeTriangles() override;
    string getType() override { return "cylinder"; }
};

class Polyline: public Shape{
public:
    Matrix points;
    Polyline(Matrix& pts) : points(pts) {}
    Matrix computePoints() override { return points; }
    StlShape computeTriangles() override {return {};};
    string getType() override { return "polyline"; }
};

class BezierCurve: public Shape{
public:
    Matrix controlPoints;
    BezierCurve(Matrix& points);
    Matrix computePoints() override { return controlPoints; }
    void draw();

    StlShape computeTriangles() override {return {};};
    string getType() override { return "bezier curve"; }
};