#include "geometry.h"

Cylinder::Cylinder(double r,  double h): r(r), h(h) {}

vvd Cylinder::computePoints() {
    vvd dataPoints;
    int steps = 50; 
    double zBottom = z - h / 2;  // Adjust base to center the cylinder
    double zTop = z + h / 2;     // Adjust top accordingly
   
    for (int i = 0; i <= steps; i++) {
        double theta = 2 * M_PI * i / steps;
        double dx = x + r * cos(theta);
        double dy = y + r * sin(theta);
        double dz = zBottom;
        dataPoints.push_back({dx, dy, dz});
    }
    dataPoints.push_back({NAN, NAN, NAN});  

    for (int i = 0; i <= steps; i++) {
        double theta = 2 * M_PI * i / steps;
        double dx = x + r * cos(theta);
        double dy = y + r * sin(theta);
        double dz = zTop;
        dataPoints.push_back({dx, dy, dz});
    }
    dataPoints.push_back({NAN, NAN, NAN});  

    for (int i = 0; i <= steps; i += steps/20) {
        double theta = 2 * M_PI * i / steps;
        double dx = x + r * cos(theta);
        double dy = y + r * sin(theta);

        // Connect bottom to top
        dataPoints.push_back({dx, dy, zBottom});
        dataPoints.push_back({dx, dy, zTop});
        dataPoints.push_back({NAN, NAN, NAN}); 
    }

    return dataPoints;
}

void Cylinder::input() {
    cout <<"Enter (r & h): "; 
    cin >> r >> h;
}

StlShape Cylinder::computeTriangles() {
    StlShape triangles;

    int segments = 50;
    double angleStep = 2 * M_PI / segments;
    double halfHeight = h / 2.0;

    // Top and bottom center points
    Vector centerTop = {x, y + halfHeight, z};
    Vector centerBottom = {x, y - halfHeight, z};

    // Generate vertices and triangles
    for (int i = 0; i < segments; ++i) {
        double theta1 = i * angleStep;
        double theta2 = (i + 1) % segments * angleStep;

        // Points on top and bottom circles
        Vector top1 = {x + r * cos(theta1), y + halfHeight, z + r * sin(theta1)};
        Vector top2 = {x + r * cos(theta2), y + halfHeight, z + r * sin(theta2)};
        Vector bottom1 = {x + r * cos(theta1), y - halfHeight, z + r * sin(theta1)};
        Vector bottom2 = {x + r * cos(theta2), y - halfHeight, z + r * sin(theta2)};

        // Top face triangle (fan from center)
        triangles.emplace_back(ThreeDUtils::computeNormal(centerTop, top1, top2), centerTop, top1, top2);

        // Bottom face triangle (fan from center, reversed winding)
        triangles.emplace_back(ThreeDUtils::computeNormal(centerBottom, bottom2, bottom1), centerBottom, bottom2, bottom1);

        // Side faces (as two triangles per quad)
        triangles.emplace_back(ThreeDUtils::computeNormal(top1, top2, bottom2), top1, top2, bottom2);
        triangles.emplace_back(ThreeDUtils::computeNormal(top1, bottom2, bottom1), top1, bottom2, bottom1);
    }

    return triangles;
}
