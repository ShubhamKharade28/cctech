#pragma once

#include "point.h"
#include <bits/stdc++.h>
using namespace std;

class BezierCurve {
    vector<Point> controlPoints;
    int numOfCurvePoints;

    public:
    BezierCurve(int n = 20){
        controlPoints = {};
        numOfCurvePoints = n;
    }

    void addControlPoint(double x, double y);
    void addControlPoint(Point p);
    
    void modifyControlPoint(int index, double x, double y);

    vector<Point> getCurvePoints();
};