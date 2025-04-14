#pragma once;

class Shape {
public:
    virtual Matrix computePoints() = 0;
    virtual StlShape computeTriangles() = 0;

    virtual void input() = 0;
    virtual string getType() { return "(shape)"; }

    virtual ~Shape() {};
};