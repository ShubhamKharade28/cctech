#include "bezier_curve.h"

void BezierCurve::addControlPoint(double x, double y){
    Point p(x,y);
    controlPoints.push_back(p);
}

void BezierCurve::addControlPoint(Point p){
    controlPoints.push_back(p);
}

void BezierCurve::moveControlPoint(int index, double x, double y){
    controlPoints[index] = Point(x,y);
}

void BezierCurve::removeControlPoint(int index){
    controlPoints.erase(controlPoints.begin() + index);
}

void BezierCurve::clearControlPoints(){
    controlPoints.clear();
}

int BezierCurve::getResolution(){
    return resolution;
}

void BezierCurve::setResolution(int n){
    resolution = n;
}

vector<Point> BezierCurve::getControlPoints(){
    return controlPoints;
}

vector<Point> BezierCurve::getCurvePoints(bool recalculate){
    if(recalculate) {
        curvePoints = calculateCurvePoints();
    }
    return curvePoints;
}

vector<Point> BezierCurve::calculateCurvePoints()  {
    curvePoints.clear();
    if(controlPoints.size() < 2) {
        return curvePoints;
    }
    int n = controlPoints.size() - 1;
    // calculate using de Casteljau's algorithm
    for(int i = 0; i <= resolution; i++){
        double t = (double)i / resolution; // t -> [0,1], interpolating parameter (alpha)
        vector<Point> points = controlPoints;
        for(int j = 1; j <= n; j++){
            for(int k = 0; k < n - j + 1; k++){
                double x = (1 - t) * points[k].x + t * points[k + 1].x;
                double y = (1 - t) * points[k].y + t * points[k + 1].y;
                points[k] = Point(x, y);
            }
        }
        curvePoints.push_back(points[0]);
    }
    return curvePoints;
}