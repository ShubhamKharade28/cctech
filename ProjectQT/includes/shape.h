#pragma once

#include "threed-utils.h"

class Shape {
protected:
    double x=0, y=0, z=0;
public:
    virtual Matrix computePoints() = 0;
    virtual StlShape computeTriangles() = 0;

    virtual void input() = 0;
    virtual string getType() { return "(shape)"; }

    virtual ~Shape() {};
};