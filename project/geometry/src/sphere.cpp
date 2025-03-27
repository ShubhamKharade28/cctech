#include "geometry.h"

Sphere::Sphere(double r, double x, double y, double z): r(r), x(x), y(y), z(z) {}

vvd Sphere::computePoints() {
    vvd dataPoints;

    int lat_steps = 20;
    int lon_steps = 20;

    // longitude lines
    for(int i=0; i<=lat_steps; i++){
        double theta = M_PI * i / lat_steps;
        for(int j=0; j<=lon_steps; j++){
            double phi = 2 * M_PI * j / lon_steps;

            double dx = x + r * sin(theta) * cos(phi);
            double dy = y + r * sin(theta) * sin(phi);
            double dz = z + r * cos(theta);
            dataPoints.push_back({dx, dy, dz});
        }
        dataPoints.push_back({NAN, NAN, NAN});
    }

    // lattitude lines
    lon_steps /= 2;
    for (int j = 0; j <= lon_steps; j++) {  
        double phi = 2 * M_PI * j / lon_steps;  

        for (int i = 0; i <= lat_steps; i++) {
            double theta = M_PI * i / lat_steps; 

            double dx = x + r * sin(theta) * cos(phi);
            double dy = y + r * sin(theta) * sin(phi);
            double dz = z + r * cos(theta);

            dataPoints.push_back({dx, dy, dz});
        }
        dataPoints.push_back({NAN, NAN, NAN}); 
    }

    return dataPoints;
}

void Sphere::input() {
    cout <<"Enter center (x, y, z): ";
    cin >> x >> y >> z;

    cout <<"Enter radius (r): ";
    cin >> r;
}