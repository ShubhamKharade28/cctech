#include "geometry.h"

Circle::Circle(double x, double y, double z, double r): 
    x(x), y(y), z(z), r(r) {}

vvd Circle::computePoints() {
    vvd dataPoints;

    int numPoints = 100;
    for (int i = 0; i <= numPoints; i++) {
        double theta = 2 * M_PI * i / numPoints;
        double px = x + r * cos(theta);
        double py = y + r * sin(theta);

        dataPoints.push_back({px, py, z});
    }

    return dataPoints;
}

void Circle::input() {
    cout << "Enter center x & y: ";
    cin >> x >> y;

    cout << "Enter radius: ";
    cin >> r;

    // cout << "Is 3D? (0/1): ";
    // cin >> is3D;
    
    z = 10;
}