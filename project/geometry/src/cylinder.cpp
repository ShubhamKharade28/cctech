#include "geometry.h"

Cylinder::Cylinder(double r,  double h, double x, double y, double z): r(r), h(h), x(x), y(y), z(z)  {
    setPivot(x,y,z);
}

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