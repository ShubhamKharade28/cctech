#include "shapes.h"

Cuboid::Cuboid(double l, double b, double h): l(l), b(b), h(h) {}

typedef std::pair<int, int> pi;

Matrix Cuboid::computePoints() {

    double halfL = l / 2.0;
    double halfB = b / 2.0;
    double halfH = h / 2.0;

    Matrix vertices = {
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

    Matrix dataPoints;
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

    double hl = l / 2.0;
    double hb = b / 2.0;
    double hh = h / 2.0;

    Matrix V = {
        {x - hl, y - hb, z - hh}, {x + hl, y - hb, z - hh},
        {x + hl, y + hb, z - hh}, {x - hl, y + hb, z - hh},
        {x - hl, y - hb, z + hh}, {x + hl, y - hb, z + hh},
        {x + hl, y + hb, z + hh}, {x - hl, y + hb, z + hh}
    };

    int faces[6][4] = {
        {0, 1, 2, 3}, // Bottom
        {4, 5, 6, 7},// Top
        {0, 3, 7, 4}, // Left
        {2, 3, 7, 6}, // Back
        {1, 2, 6, 5}, // Right
        {0, 1, 5, 4} // Front
    };

    for (auto& f : faces) {
        auto v0 = V[f[0]];
        auto v1 = V[f[1]];
        auto v2 = V[f[2]];
        auto v3 = V[f[3]];

        // Vector n1 = ::computeNormal(v0, v1, v2);
        // Vector n2 = ThreeDUtils::computeNormal(v0, v2, v3);

        triangles.push_back(Triangle(v0, v1, v2));
        triangles.push_back(Triangle(v0, v2, v3));
    }

    return triangles;
}

Cube::Cube(double side): 
    Cuboid(side, side, side), side(side) {}