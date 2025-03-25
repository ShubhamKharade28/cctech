#include "geometry.h"

Rectangle::Rectangle(double x, double y, double l, double b) : x(x), y(y), l(l), b(b) {}

void Rectangle::draw() {
    GnuplotUtils gp;
    
    vector<pd> vertices = {
        {x, y},          // Bottom-left
        {x + l, y},      // Bottom-right
        {x + l, y + b},  // Top-right
        {x, y + b},      // Top-left
        {x, y}           // Closing the rectangle (Back to Bottom-left)
    };

    gp.plot2D(vertices, "rectangle");
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