#include "drawable-shape.h"

DrawableShape::DrawableShape(shared_ptr<Shape> baseShape, string name, int id)
    : shape(baseShape), name(name), id(id), 
    position({0,0,0}), rotation({0,0,0}),
    scale(0), color({1,1,1}) {}

void DrawableShape::setPosition(Vector p) { position = p; }
void DrawableShape::setRotation(Vector r) { rotation = r; }
void DrawableShape::setScale(double s) { scale = s; }

void DrawableShape::setColor(Vector c) { color = c; }

string DrawableShape::getName() { return name; }
int DrawableShape::getId() { return id; }

Vector DrawableShape::getColor() { return color; }

StlShape DrawableShape::getTriangles() {
    StlShape triangles = shape->computeTriangles();
    
    // StlShape = vector<Triangle>
    // TODO: Apply transformations before returning

    return triangles;
}

shared_ptr<Shape> DrawableShape::getShape() {
    return shape;
}

string DrawableShape::getType() { return shape->getType(); }