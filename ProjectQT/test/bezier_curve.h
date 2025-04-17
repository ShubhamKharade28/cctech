#pragma once

#include "point.h"
#include <bits/stdc++.h>
using namespace std;

class BezierCurve {
    int resolution; // number of curve points
    vector<Point> controlPoints;
    vector<Point> curvePoints;

    public:
    BezierCurve(int n = 50){
        controlPoints = {};
        resolution = n;
    }

    int getResolution();
    void setResolution(int n = 50);

    void addControlPoint(double x, double y);
    void addControlPoint(Point p);
    
    void moveControlPoint(int index, double x, double y);
    void removeControlPoint(int index);
    void clearControlPoints();

    vector<Point> getCurvePoints(bool recalculate = false);
    vector<Point> getControlPoints();

    int findControlPoint(double x, double y, double influenceRadius = 0.5){
        // fint the control point closes to (x,y) and within influenceRadius
        for(int i = 0; i < controlPoints.size(); i++){
            if (sqrt(pow(controlPoints[i].x - x, 2) + pow(controlPoints[i].y - y, 2)) <= influenceRadius){
                return i;
            }
        }
        return -1; // not found
    }

private:
    vector<Point> calculateCurvePoints();
};
