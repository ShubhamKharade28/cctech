#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "threed-utils.h"

class DrawableShape {
private:
    // base shape
    shared_ptr<Shape> shape;

    // transformations and color
    Vector translation; 
    Vector rotation;     
    double scale;       
    Vector color;

    // metadata
    string name;
    int id;
public:
    DrawableShape(shared_ptr<Shape> baseShape, string name, int id=-1);
    
    void setTranslation(Vector t);
    void setRotation(Vector rotation);
    void setScale(double scale);
    void setColor(Vector color);

    string getName();
    int getId();
    Vector getColor();
    string getType();

    StlShape getTriangles();

    shared_ptr<Shape> getShape();
};