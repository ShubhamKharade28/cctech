#include "geometry.h"

Cuboid::Cuboid(double l, double b, double h, double x, double y, double z): l(l), b(b), h(h), x(x), y(y), z(z) {
    setPivot(x, y, z);
}

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
}

StlShape Cuboid::computeTriangles() {
    StlShape triangles;

    Matrix V = {
        {0, 0, 0}, {l, 0, 0}, {l, b, 0}, {0, b, 0},
        {0, 0, h}, {l, 0, h}, {l, b, h}, {0, b, h}
    };

    int faces[6][4] = {
        {0, 1, 5, 4}, // Front
        {1, 2, 6, 5}, // Right
        {2, 3, 7, 6}, // Back
        {0, 3, 7, 4}, // Left
        {0, 1, 2, 3}, // Bottom
        {4, 5, 6, 7} // Top
    };

    for (auto& f : faces) {
        auto v0 = V[f[0]];
        auto v1 = V[f[1]];
        auto v2 = V[f[2]];
        auto v3 = V[f[3]];

        Vector n1 = ThreeDUtils::computeNormal(v0, v1, v2);
        Vector n2 = ThreeDUtils::computeNormal(v0, v2, v3);

        triangles.push_back(Triangle(n1, v0, v1, v2));
        triangles.push_back(Triangle(n2, v0, v2, v3));
    }

    return triangles;
}

Cube::Cube(double x, double y, double z, double side): 
    Cuboid(x, y, z, side, side, side), side(side) {}