#include "geometry.h"

Circle::Circle(double x, double y, double z, double r, bool is3D): 
    x(x), y(y), z(z), r(r), is3D(is3D) {}

void Circle::draw() {
    GnuplotUtils gp;
    vector<pair<double, double>> points2D;
    vector<tuple<double, double, double>> points3D;

    int numPoints = 100;
    for (int i = 0; i <= numPoints; i++) {
        double theta = 2 * M_PI * i / numPoints;
        double px = x + r * cos(theta);
        double py = y + r * sin(theta);

        if (is3D)
            points3D.emplace_back(px, py, z);
        else
            points2D.emplace_back(px, py);
    }

    if (is3D)
        gp.plot3D(points3D, "Circle");
    else
        gp.plot2D(points2D, "Circle");
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