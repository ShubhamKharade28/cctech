#include "bezier_curve.h"

void BezierCurve::addControlPoint(double x, double y){
    Point p(x,y);
    controlPoints.push_back(p);
}

void BezierCurve::addControlPoint(Point p){
    controlPoints.push_back(p);
}

void BezierCurve::modifyControlPoint(int index, double x, double y){
    controlPoints[index] = Point(x,y);
}

vector<Point> BezierCurve::getCurvePoints()  {
    double dAlpha = 1/numOfCurvePoints; // change in alpha 
    double currAlpha = 0;

    vector<Point> points = controlPoints;

    vector<pair<Point, Point>> lines;
    for(int i=0; i<numOfCurvePoints; i++){
        currAlpha = dAlpha;
        for(int j=0; j<points.size()-1; j++){
            double x1 = points[j].x, y1 = points[j].y;
            double x2 = points[j+1].x, y2 = points[j+1].y;

            currAlpha += dAlpha;
        }
    }

    return {};
}