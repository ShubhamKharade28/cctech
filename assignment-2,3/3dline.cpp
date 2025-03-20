#include <bits/stdc++.h>
#include "gnuplot-iostream.h"
using namespace std;

#include "lib/point.cpp"

vector<Point3D> generatePoints(Point3D p1, Point3D p2){
    vector<Point3D> points;
    
    double dx = (p2.x - p1.x) / 9.0;  
    double dy = (p2.y - p1.y) / 9.0;
    double dz = (p2.z - p1.z) / 9.0;

    for (int i = 0; i < 10; i++) {
        double x = p1.x + i * dx;
        double y = p1.y + i * dy;
        double z = p1.z + i * dz;
        Point3D p(x,y,z);
        points.push_back(p);
    }

    return points;
}

void print(vector<Point3D>& points){
    cout << "Point3Ds: "<<endl;
    for(auto& point : points){
        cout << point.x << "\t" << point.y << "\t" << point.y << endl;
    }
    cout << endl;
}

vector<tuple<double,double,double>> pointToTuple(vector<Point3D>& points){
    vector<tuple<double,double,double>> res;
    for(auto& point : points){
        res.push_back({point.x, point.y, point.z});
    }
    return res;
}

int main(){
    // input start and end coordinates
    double x1,x2,y1,y2,z1,z2;
    cout << "Enter start coords: ";
    cin >> x1 >> y1 >> z1;
    cout << "Enter end coords: ";
    cin >> x2 >> y2 >> z2;

    Point3D p1(x1,y1,z1);
    Point3D p2(x2,y2,z2);

    // generate points from start to end to plot
    vector<Point3D> points = generatePoints(p1,p2);
    vector<tuple<double,double,double>> coords = pointToTuple(points);

    // setup gnuplot
    Gnuplot gp;
    gp << "set terminal wxt\n";
    // gp << "set terminal dumb\n";

    // Set Gnuplot options for 3D plotting
    gp << "set xlabel 'X'\n";          // Label X-axis
    gp << "set ylabel 'Y'\n";          // Label Y-axis
    gp << "set zlabel 'Z'\n";          // Label Z-axis
    gp << "set title '3D Line Plot'\n"; // Title
    gp << "splot '-' with lines\n";    // Plot data as a 3D line

    gp.send1d(coords);
}