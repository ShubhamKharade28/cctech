#include "geometry.h"

Cuboid::Cuboid(double x, double y, double z, double l, double b, double h): 
    l(l), b(b), h(h), x(x), y(y), z(z) {} 

void Cuboid::draw(){
    GnuplotUtils gp;
    vector<td> vertices = {
        {x, y, z},                // 0: left-bottom-front  
        {x + l, y, z},            // 1: right-bottom-front
        {x + l, y + b, z},        // 2: right-top-front
        {x, y + b, z},            // 3: left-top-front
        {x, y, z + h},            // 4: left-bottom-back
        {x + l, y, z + h},        // 5: right-bottom-back
        {x + l, y + b, z + h},    // 6: right-top-back
        {x, y + b, z + h}         // 7: left-top-back
    };

    vector<pi> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Front face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Back face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
    };

    vector<td> plotData;
    for(pi& edge : edges){
        plotData.push_back(vertices[edge.first]);
        plotData.push_back(vertices[edge.second]);
        plotData.push_back({NAN,NAN,NAN});
    }

    gp.draw3D(plotData, "mycuboid.dat", "My Cuboid");
}


Cube::Cube(double x, double y, double z, double side): 
    Cuboid(x, y, z, side, side, side), side(side) {}