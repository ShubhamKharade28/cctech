#pragma once

class Point {
    public:
    double x,y;

    Point(double x=0, double y=0) : x(x), y(y) {}
};

class Point3d : public Point {
    public:
    double z;
    Point3d(double x=0, double y=0, double z=0) : Point(x,y), z(z) {}
};