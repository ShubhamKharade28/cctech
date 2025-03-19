#include <bits/stdc++.h>
#include "gnuplot-iostream.h"
using namespace std;

vector<pair<double,double>> generatePoints(double x1, double y1, double x2, double y2){
    vector<pair<double, double>> points;
    
    double dx = (x2 - x1) / 9.0;  
    double dy = (y2 - y1) / 9.0;

    for (int i = 0; i < 10; i++) {
        double x = x1 + i * dx;
        double y = y1 + i * dy;
        points.push_back({x, y});
    }

    return points;
}

int main(){
    // setup gnuplot and it's terminal (qt, x11 and wxt aren't working)
    Gnuplot gp;
    gp << "set terminal dumb\n";

    // input start and end coordinates
    double x1,x2,y1,y2;
    cout << "Enter start coords: ";
    cin >> x1 >> y1;
    cout << "Enter end coords: ";
    cin >> x2 >> y2;

    // generate points from start to end to plot
    vector<pair<double,double>> points = generatePoints(x1,y1,x2,y2);

    // plot the points
    gp << "plot '-' with lines title 'y = x^2'\n";
    gp.send1d(points);
}

