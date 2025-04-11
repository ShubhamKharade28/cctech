#include "geometry.h"

Rectangle::Rectangle(double l, double b): l(l), b(b) {}

vvd Rectangle::computePoints() {
    double half_l = l / 2.0;
    double half_b = b / 2.0;
    vvd vertices = {
        {x - half_l, y - half_b, z},  // Bottom-left
        {x + half_l, y - half_b, z},  // Bottom-right
        {x + half_l, y + half_b, z},  // Top-right
        {x - half_l, y + half_b, z},  // Top-left
        {x - half_l, y - half_b, z}   // Closing the rectangle (Back to Bottom-left)
    };
    return vertices;
}

void Rectangle::input() {
    cout <<"Enter length & breadth: ";
    cin >> l >> b;
}