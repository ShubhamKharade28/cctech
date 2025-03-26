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

template class Line<Point>;
template class Line<Point3D>;
