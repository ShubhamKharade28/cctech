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

    int findControlPoint(double x, double y, double influenceRadius);

private:
    vector<Point> calculateCurvePoints();
};
