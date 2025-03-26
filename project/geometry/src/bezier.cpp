#include "geometry.h"

void Polyline::draw() {
    vvd points = getDrawable();
    GnuplotUtils gp;
    gp.plot3D(points);
}

BezierCurve::BezierCurve(vvd& points):
    controlPoints(points) {}

void BezierCurve::draw() {
    GnuplotUtils gp;
    vvd controlPoints = getDrawable();
    gp.plotCurve(controlPoints, "Smooth Curve");
}