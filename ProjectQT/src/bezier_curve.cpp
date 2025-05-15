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

int BezierCurve::findControlPoint(double x, double y, double influenceRadius = 0.5) {
    // fint the control point closes to (x,y) and within influenceRadius
    for(int i = 0; i < controlPoints.size(); i++){
        if (sqrt(pow(controlPoints[i].x - x, 2) + pow(controlPoints[i].y - y, 2)) <= influenceRadius){
            return i;
        }
    }
    return -1; // not found
}

optional<Point> intersectSegments(Point& A, Point& B, Point& C, Point& D) {
    double denom = (A.x - B.x) * (C.y - D.y) - (A.y - B.y) * (C.x - D.x);
    if (fabs(denom) < 1e-10) return nullopt;

    double numX = (A.x * B.y - A.y * B.x) * (C.x - D.x) - (A.x - B.x) * (C.x * D.y - C.y * D.x);
    double numY = (A.x * B.y - A.y * B.x) * (C.y - D.y) - (A.y - B.y) * (C.x * D.y - C.y * D.x);
    double x = numX / denom;
    double y = numY / denom;

    // Check if (x, y) is on both segments
    auto onSegment = [](Point& p1, Point& p2, Point& p) {
        return min(p1.x, p2.x) - 1e-8 <= p.x && p.x <= max(p1.x, p2.x) + 1e-8 &&
               min(p1.y, p2.y) - 1e-8 <= p.y && p.y <= max(p1.y, p2.y) + 1e-8;
    };

    Point intersection{x, y};
    if (onSegment(A, B, intersection) && onSegment(C, D, intersection)) {
        return intersection;
    }

    return nullopt;
}

vector<Point> BezierCurve::findIntersectionWith(BezierCurve* otherCurve) {
    vector<Point> intersections;
    vector<Point> othersCurvePoints = otherCurve->getCurvePoints();

    for (int i = 0; i + 1 < curvePoints.size(); ++i) {
        for (int j = 0; j + 1 < othersCurvePoints.size(); ++j) {
            auto inter = intersectSegments(curvePoints[i], curvePoints[i + 1],
                                           othersCurvePoints[j], othersCurvePoints[j + 1]);
            if (inter.has_value()) {
                intersections.push_back(inter.value());
            }
        }
    }

    return intersections;
}