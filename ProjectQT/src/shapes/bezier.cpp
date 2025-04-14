#include "shapes.h"

BezierCurve::BezierCurve(vvd& points):
    controlPoints(points) {}

void BezierCurve::draw() {
    GnuplotUtils gp;
    vvd controlPoints = computePoints();
    gp.plotCurve(controlPoints, "Smooth Curve");
}