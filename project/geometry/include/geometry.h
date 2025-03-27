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
    double toRadians(double degrees) {
        return degrees * M_PI / 180.0;
    }
protected:
    vector<double> translation = {0,0,0};
    vector<double> rotation = {0,0,0};
    double scaleFactor = 1.0;
    vector<double> pivot = {0,0,0};
    string title = "3D Shape";
    string filename = "shape-data.dat";
public:
    virtual vvd computePoints() = 0;
    virtual void draw();
    vvd getDrawable();

    void setTitle(string title);
    void setFileName(string filename);
    void setRotation(double rx, double ry, double rz);
    void setTranslation(double cx, double cy, double cz);
    void setScaling(double factor);
    void setPivot(double px, double py, double pz);
    virtual void input() = 0;

    void inputTransformation() {
        cout << "Any rotation? (y/n): ";
        char isRotation = 'n'; cin >> isRotation;

        if(isRotation == 'y' ) {
            cout <<"Enter (rx, ry, rz): ";
            double rx, ry, rz; 
            cin >> rx >> ry >> rz;
            
            setRotation(rx, ry, rz);
        }
    }

    virtual ~Shape() {};
};

class Rectangle: public Shape {
public:
    double l,b;
    double x,y,z;
    
    Rectangle(double x=0, double y=0, double z=0, double l=1, double b=1);
    vvd computePoints() override;
    void input();
    Rectangle rotate90();
};

class Cuboid: public Shape {
public:
    double l, b, h;
    double x, y, z;
    Cuboid(double l=1, double b=1, double h=1, double x=0, double y=0, double z=0);
    vvd computePoints() override;
    void input() override;
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
    void input() ;
    vvd computePoints() override;
};

class Sphere: public Shape{
public:
    double r,x,y,z;
    Sphere(double r=1, double x=0, double y=0, double z=0);
    vvd computePoints() override;
    void input() override;
};

class Cylinder: public Shape {
public:
    double x, y, z; 
    double r, h;
    Cylinder(double r=1,  double h=10, double x=0, double y=0, double z=0);
    vvd computePoints() override;
    void input() override;
};

class Polyline: public Shape{
public:
    vvd points;
    Polyline(vvd& pts) : points(pts) {}
    vvd computePoints() override { return points; }
};

class BezierCurve: public Shape{
public:
    vvd controlPoints;
    BezierCurve(vvd& points);
    vvd computePoints() override { return controlPoints; }
    void draw();
};
    

#endif