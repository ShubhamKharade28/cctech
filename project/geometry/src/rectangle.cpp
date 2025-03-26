#include "geometry.h"

Rectangle::Rectangle(double x, double y, double z, double l, double b) : x(x), y(y), z(z), l(l), b(b) {}

vvd Rectangle::getDrawable() {
    vvd vertices = {
        {x, y, z},          // Bottom-left
        {x + l, y, z},      // Bottom-right
        {x + l, y + b, z},  // Top-right
        {x, y + b, z},      // Top-left
        {x, y, z}           // Closing the rectangle (Back to Bottom-left)
    };
    return vertices;
}

void Rectangle::draw() {
    GnuplotUtils gp;
    vvd dataPoints = getDrawable();
    gp.plot2D(dataPoints, "rectangle");
}

void Rectangle::input() {
    cout <<"Enter start x & y: ";
    cin >> x >> y;

    cout <<"Enter length & breadth: ";
    cin >> l >> b;
}

Rectangle Rectangle::rotate90(){
    return Rectangle(x,y,b,l);
}