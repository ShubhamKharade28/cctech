#include "shapes.h"

Circle::Circle(double r): r(r) {}

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
    cout << "Enter radius: ";
    cin >> r;
}