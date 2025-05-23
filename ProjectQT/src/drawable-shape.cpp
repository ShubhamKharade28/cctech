#include "drawable-shape.h"
#include "transformations.h"

DrawableShape::DrawableShape(shared_ptr<Shape> baseShape, string name, int id)
    : shape(baseShape), name(name), id(id), 
    position({0,0,0}), rotation({0,0,0}),
    scale(1), color({1,1,1}) {}

void DrawableShape::setPosition(Vector p) { position = p; }
void DrawableShape::setRotation(Vector r) { rotation = r; }
void DrawableShape::setScale(double s) { scale = s; }

vector<double> DrawableShape::getPosition() { return position; }
vector<double> DrawableShape::getRotation() { return rotation; }
double DrawableShape::getScale() { return scale; }

void DrawableShape::setColor(Vector c) { color = c; }

string DrawableShape::getName() { return name; }
int DrawableShape::getId() { return id; }

Vector DrawableShape::getColor() { return color; }

StlShape DrawableShape::getTriangles() {
    StlShape triangles = shape->computeTriangles();
    triangles = Transformations::applyTransformations(triangles, position, rotation, scale);
    return triangles;
}

shared_ptr<Shape> DrawableShape::getShape() {
    return shape;
}

string DrawableShape::getType() { return shape->getType(); }