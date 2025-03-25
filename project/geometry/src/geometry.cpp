
#include "geometry.h"
#define pi pair<int, int>

template <typename T>
void Line<T>::draw(){
    GnuplotUtils gp;
    if constexpr (is_same_v<T, Point3D>) {
        vector<td> plotData = {start.toTuple(), end.toTuple()};
        gp.plot3D(plotData);
    } else {
        vector<pd> plotData = {start.toPair(), end.toPair()};
        gp.plot2D(plotData);
    }
}

void Rectangle::draw() {
    GnuplotUtils gp;
    
    vector<pd> vertices = {
        {x, y},          // Bottom-left
        {x + l, y},      // Bottom-right
        {x + l, y + b},  // Top-right
        {x, y + b},      // Top-left
        {x, y}           // Closing the rectangle (Back to Bottom-left)
    };

    gp.plot2D(vertices, "rectangle");
}

void Rectangle::input() {
    cout <<"Enter start x & y: ";
    cin >> x >> y;

    cout <<"Enter length & breadth: ";
    cin >> l >> b;
}


vvd multiplyMatrix(vvd &A,vvd &B) {
    int rowsA = A.size(), colsA = A[0].size();
    int rowsB = B.size(), colsB = B[0].size();

    if (colsA != rowsB) {
        throw invalid_argument("Matrix dimensions do not match for multiplication.");
    }

    vvd result(rowsA, vector<double>(colsB, 0));

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

Rectangle Rectangle::rotate90(){
    vvd X = {{x, y}, {x+l, y},{x+l, y+b}, {x, y+b}};
    vvd T = {{0, 1}, {-1, 0}};
    vvd rotated = multiplyMatrix(X,T);
    double newX = rotated[0][0], newY = rotated[0][1];
    double newL = b, newB = l;
    Rectangle rg(newX, newY, newL, newB);
    return rg;
}

void Cuboid::draw(){
    GnuplotUtils gp;
    vector<td> vertices = {
        {x, y, z},                // 0: left-bottom-front  
        {x + l, y, z},            // 1: right-bottom-front
        {x + l, y + b, z},        // 2: right-top-front
        {x, y + b, z},            // 3: left-top-front
        {x, y, z + h},            // 4: left-bottom-back
        {x + l, y, z + h},        // 5: right-bottom-back
        {x + l, y + b, z + h},    // 6: right-top-back
        {x, y + b, z + h}         // 7: left-top-back
    };

    vector<pi> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Front face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Back face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Connecting edges
    };

    vector<td> plotData;
    for(pi& edge : edges){
        plotData.push_back(vertices[edge.first]);
        plotData.push_back(vertices[edge.second]);
        plotData.push_back({NAN,NAN,NAN});
    }

    gp.draw3D(plotData, "mycuboid.dat", "My Cuboid");
}

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

void Sphere::draw() {
    string filename = "mysphere.dat";
    vector<td> dataPoints;

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

    GnuplotUtils gp;
    gp.draw3D(dataPoints, filename, "Sphere");
}

void Cylinder::draw() {
    string filename = "mycylinder.dat";  // Save in 'data' folder
    vector<td> dataPoints;

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

    for (int i = 0; i <= steps; i += steps/50) {
        double theta = 2 * M_PI * i / steps;
        double dx = x + r * cos(theta);
        double dy = y + r * sin(theta);

        // Connect bottom to top
        dataPoints.push_back({dx, dy, z});
        dataPoints.push_back({dx, dy, z + h});
        dataPoints.push_back({NAN, NAN, NAN}); 
    }

    GnuplotUtils gp;
    gp.draw3D(dataPoints, filename, "Cylinder");
}



template class Line<Point>;
template class Line<Point3D>;
