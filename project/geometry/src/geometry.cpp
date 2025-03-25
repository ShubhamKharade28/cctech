#include "geometry.h"

template <typename T>
void Line<T>::draw(){
    GnuplotUtils gp;
    if constexpr (is_same_v<T, Point3D>) {
        vector<td> plotData = {start.toTuple(), end.toTuple()};
        gp.plot3D(plotData);
    } else {
        vector<pd> plotData = {start.toPair(), end.toPair()};
        gp.plot2D(plotData);
    }
}

template class Line<Point>;
template class Line<Point3D>;
