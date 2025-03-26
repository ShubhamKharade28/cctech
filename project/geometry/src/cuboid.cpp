#include "geometry.h"

Cuboid::Cuboid(double x, double y, double z, double l, double b, double h): 
    x(x), y(y), z(z),l(l), b(b), h(h) {
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
} 

void Cuboid::setRotation(double rotX_deg, double rotY_deg, double rotZ_deg) {
    rotationX = degToRad(rotX_deg);
    rotationY = degToRad(rotY_deg);
    rotationZ = degToRad(rotZ_deg);
}

vvd Cuboid::getDrawable() {
    vvd vertices = {
        {x, y, z},                // 0: left-bottom-front  
        {x + l, y, z},            // 1: right-bottom-front
        {x + l, y + b, z},        // 2: right-top-front
        {x, y + b, z},            // 3: left-top-front
        {x, y, z + h},            // 4: left-bottom-back
        {x + l, y, z + h},        // 5: right-bottom-back
        {x + l, y + b, z + h},    // 6: right-top-back
        {x, y + b, z + h}         // 7: left-top-back
    };

    // TODO: use transformation class for rotation
    for (auto& v : vertices) {
        double x_ = v[0] - x;
        double y_ = v[1] - y;
        double z_ = v[2] - z;

        // Rotation around X-axis
        double y1 = y_ * cos(rotationX) - z_ * sin(rotationX);
        double z1 = y_ * sin(rotationX) + z_ * cos(rotationX);

        // Rotation around Y-axis
        double x2 = x_ * cos(rotationY) + z1 * sin(rotationY);
        double z2 = -x_ * sin(rotationY) + z1 * cos(rotationY);

        // Rotation around Z-axis
        double x3 = x2 * cos(rotationZ) - y1 * sin(rotationZ);
        double y3 = x2 * sin(rotationZ) + y1 * cos(rotationZ);

        v[0] = x3 + x;
        v[1] = y3 + y;
        v[2] = z2 + z;
    }

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

void Cuboid::draw() {
    GnuplotUtils gp;
    vvd dataPoints = getDrawable();
    gp.plot3D(dataPoints);
    // gp.draw3D(dataPoints, "mycuboid.dat", "My Cuboid");
}


Cube::Cube(double x, double y, double z, double side): 
    Cuboid(x, y, z, side, side, side), side(side) {}