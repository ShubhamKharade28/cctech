
#include "geometry.h"
#define tb tuple<double,double,double>
#define pi pair<int,int>

template <typename T>
void Line<T>::draw(){
    GnuplotUtils gp;
    if constexpr (is_same_v<T, Point3D>) {
        vector<tuple<double, double, double>> plotData = {start.toTuple(), end.toTuple()};
        gp.plot3D(plotData);
    } else {
        vector<pair<double, double>> plotData = {start.toPair(), end.toPair()};
        gp.plot2D(plotData);
    }
}

void Rectangle::draw() {
    GnuplotUtils gp;
    
    vector<pair<double, double>> vertices = {
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

void Cuboid::draw(){
    GnuplotUtils gp;
    vector<tb> vertices = {
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

    vector<tb> plotData;
    for(pi& edge : edges){
        plotData.push_back(vertices[edge.first]);
        plotData.push_back(vertices[edge.second]);
        plotData.push_back({NAN,NAN,NAN});
    }

    gp.plot3D(plotData);
}

template class Line<Point>;
template class Line<Point3D>;