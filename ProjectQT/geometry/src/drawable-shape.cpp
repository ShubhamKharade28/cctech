#include "drawable-shape.h"

DrawableShape::DrawableShape(shared_ptr<Shape> baseShape, string name, int id)
    : shape(baseShape), name(name), id(id), 
    translation({0,0,0}), rotation({0,0,0}),
    scale(0), color({1,1,1}) {}

void DrawableShape::setTranslation(Vector t) { translation = t; }
void DrawableShape::setRotation(Vector r) { rotation = r; }
void DrawableShape::setScale(double s) { scale = s; }

void DrawableShape::setColor(Vector c) { color = c; }

string DrawableShape::getName() { return name; }
int DrawableShape::getId() { return id; }

Vector DrawableShape::getColor() { return color; }

StlShape DrawableShape::getTriangles() {
    StlShape triangles = shape->computeTriangles();
    Transformations tf;

    if(scale != 1.0) {
        triangles = tf.scaleShape(triangles, scale);
    }

    if(rotation[0] != 0 || rotation[1] != 0 || rotation[2] != 0){
        triangles = tf.translateShape(triangles, rotation);
    }

    if (translation[0] != 0 || translation[1] != 0 || translation[2] != 0) {
        triangles = tf.translateShape(triangles, translation);
    }

    return triangles;
}

shared_ptr<Shape> DrawableShape::getShape() {
    return shape;
}

string DrawableShape::getType() { return shape->getType(); }