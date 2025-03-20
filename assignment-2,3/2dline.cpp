#include <bits/stdc++.h>
#include "gnuplot-iostream.h"
using namespace std;

#include "lib/point.cpp"

vector<Point2D> generatePoints(Point2D p1, Point2D p2){
    vector<Point2D> points;
    
    double dx = (p2.x - p1.x) / 9.0;  
    double dy = (p2.y - p1.y) / 9.0;

    for (int i = 0; i < 10; i++) {
        double x = p1.x + i * dx;
        double y = p1.y + i * dy;
        points.push_back(Point2D(x,y));
    }

    return points;
}

int main(){
    // setup gnuplot and it's terminal (qt, x11 and wxt aren't working)
    Gnuplot gp;
    gp << "set terminal dumb\n";

    // input start and end coordinates
    Point2D p1, p2;
    cout << "Enter start coords: ";
    cin >> p1.x >> p1.y;
    cout << "Enter end coords: ";
    cin >> p2.x >> p2.y

    // generate points from start to end to plot
    vector<Point2D> points = generatePoints(p1,p2);

    // plot the points
    gp << "plot '-' with lines title 'y = x^2'\n";
    gp.send1d(points);
}

// DAA - CLR 