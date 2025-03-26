#include "geometry.h"

vvd Cylinder::getDrawable() {
    vvd dataPoints;
    int steps = 50; 
   
    for (int i = 0; i <= steps; i++) {
        double theta = 2 * M_PI * i / steps;
        double dx = x + r * cos(theta);
        double dy = y + r * sin(theta);
        double dz = z; // bottom base
        dataPoints.push_back({dx, dy, dz});
    }
    dataPoints.push_back({NAN, NAN, NAN});  

    for (int i = 0; i <= steps; i++) {
        double theta = 2 * M_PI * i / steps;
        double dx = x + r * cos(theta);
        double dy = y + r * sin(theta);
        double dz = z + h; // top base
        dataPoints.push_back({dx, dy, dz});
    }
    dataPoints.push_back({NAN, NAN, NAN});  

    for (int i = 0; i <= steps; i += steps/20) {
        double theta = 2 * M_PI * i / steps;
        double dx = x + r * cos(theta);
        double dy = y + r * sin(theta);

        // Connect bottom to top
        dataPoints.push_back({dx, dy, z});
        dataPoints.push_back({dx, dy, z + h});
        dataPoints.push_back({NAN, NAN, NAN}); 
    }

    return dataPoints;
}

void Cylinder::draw() {
    GnuplotUtils gp;
    // string filename = "mycylinder.dat";
    // gp.draw3D(dataPoints, filename, "Cylinder");
    vvd dataPoints = getDrawable();
    gp.plot3D(dataPoints);
}