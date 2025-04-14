#include "threed-utils.h"

Vector substract(Vector a, Vector b){
    return {a[0]-b[0], a[1]-b[1], a[2]-b[2]};
}

Vector cross(Vector a, Vector b){
    return {
        a[1]*b[2] - a[2]*b[1],
        a[2]*b[0] - a[0]*b[2],
        a[0]*b[1] - a[1]*b[0]
    };
}

double magnitude(Vector v) {
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

Vector normalize(Vector v) {
    double mag = magnitude(v);
    if (mag == 0) return {0, 0, 0}; // avoid division by zero
    return {v[0]/mag, v[1]/mag, v[2]/mag};
}

Vector Triangle::getNormal() {
    return computeNormal(vertex1, vertex2, vertex3);
}

Vector Triangle::computeNormal(Vector v1, Vector v2, Vector v3); {
    Vector edge1 = substract(vertex2, vertex1);
    Vector edge2 = substract(vertex3, vertex1);
    return normalize(cross(edge1, edge2));
}

Triangle::Triangle(Vector n, Vector v1, Vector v2, Vector v3): 
    normal(n), vertex1(v1), vertex2(v2), vertex3(v3) {}

Triangle::Triangle(Vector v1, Vector v2, Vector v3): vertex1(v1), vertex2(v2), vertex3(v3) {
    this->normal = getNormal();
}

