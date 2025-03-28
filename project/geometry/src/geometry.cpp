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

void Shape::setTitle(string title) {
    this->title = title;
}   

void Shape::setFileName(string filename) {
    this->filename = filename;
}

void Shape::setTranslation(double cx, double cy, double cz) {
    translation = {cx, cy, cz};
}

void Shape::setRotation(double rx, double ry, double rz) {
    rotation = {rx, ry, rz};
}

void Shape::setScaling(double factor){
    scaleFactor = factor;
}

void Shape::setPivot(double px, double py, double pz){
    pivot = {px, py, pz};
}

vvd Shape::getDrawable() {
    vvd points = computePoints();

    Transformations transform;
    points = transform.scale(points, scaleFactor, pivot);
    points = transform.rotate(points, rotation[0], 'x', pivot);
    points = transform.rotate(points, rotation[1], 'y', pivot);
    points = transform.rotate(points, rotation[2], 'z', pivot);
    points = transform.translate(points, translation[0], translation[1], translation[2]);

    return points;
}

void Shape::draw() {
    vvd points = getDrawable();
    GnuplotUtils gp;
    cout << "Drawing my shape..."<< endl;
    gp.plot3D(points, "My shape");
}

void Shape::inputTransformation() {
    cout <<"Enter rotation(rx, ry, rz): ";
    double rx, ry, rz; 
    cin >> rx >> ry >> rz;
    setRotation(rx, ry, rz);

    cout <<"Enter translation(cx, cy, cz): ";
    double cx, cy, cz;
    cin >> cx >> cy >> cz;
    setTranslation(cx, cy, cz);
}

void Shape::addTranslation(char axis='x', double val=1) {
    double cx = translation[0], cy = translation[1], cz = translation[2];
    if(axis == 'x'){
        cx += val;
    } else if(axis == 'y') {
        cy += val;
    } else {
        cz += val;
    }
    setTranslation(cx, cy, cz);
}

template class Line<Point>;
template class Line<Point3D>;
