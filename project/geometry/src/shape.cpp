#include "geometry.h"

template <typename T>
void Line<T>::draw(){
    GnuplotUtils gp;
    vvd dataPoints = {start.toVector(), end.toVector()};
    if constexpr (is_same_v<T, Point3D>) {
        gp.plot3D(dataPoints);
    } else {
        gp.plot2D(dataPoints);
    }
}

vvd Shape::getDrawable() {
    vvd points = computePoints();

    // Transformations transform;
    // points = transform.scale(points, scaleFactor, pivot);
    // points = transform.rotate(points, rotation[0], 'x', pivot);
    // points = transform.rotate(points, rotation[1], 'y', pivot);
    // points = transform.rotate(points, rotation[2], 'z', pivot);
    // points = transform.translate(points, translation[0], translation[1], translation[2]);

    return points;
}

void Shape::draw() {
    vvd points = getDrawable();
    GnuplotUtils gp;
    cout << "Drawing my shape..."<< endl;
    gp.plot3D(points, "My shape");
}

template class Line<Point>;
template class Line<Point3D>;
