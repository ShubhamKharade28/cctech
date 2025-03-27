#include "geometry.h"

Cuboid::Cuboid(double l, double b, double h, double x, double y, double z): l(l), b(b), h(h), x(x), y(y), z(z) {}

vvd Cuboid::computePoints() {
    double halfL = l / 2.0;
    double halfB = b / 2.0;
    double halfH = h / 2.0;

    vvd vertices = {
        {x - halfL, y - halfB, z - halfH},  // 0: left-bottom-front  
        {x + halfL, y - halfB, z - halfH},  // 1: right-bottom-front
        {x + halfL, y + halfB, z - halfH},  // 2: right-top-front
        {x - halfL, y + halfB, z - halfH},  // 3: left-top-front
        {x - halfL, y - halfB, z + halfH},  // 4: left-bottom-back
        {x + halfL, y - halfB, z + halfH},  // 5: right-bottom-back
        {x + halfL, y + halfB, z + halfH},  // 6: right-top-back
        {x - halfL, y + halfB, z + halfH}   // 7: left-top-back
    };

    vector<pi> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Front face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Back face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
    };

    vvd dataPoints;
    for(pi& edge : edges){
        dataPoints.push_back(vertices[edge.first]);
        dataPoints.push_back(vertices[edge.second]);
        dataPoints.push_back({NAN,NAN,NAN});
    }

    return dataPoints;
}

void Cuboid::input() {
    cout <<"Enter (l,b,h): ";
    cin >> l >> b >> h;

    cout <<"Enter (x,y,z): ";
    cin >> x >> y >> z;
}

Cube::Cube(double x, double y, double z, double side): 
    Cuboid(x, y, z, side, side, side), side(side) {}