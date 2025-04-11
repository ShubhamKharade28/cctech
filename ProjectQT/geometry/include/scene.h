#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "drawable-shape.h"

class Scene {
    string name;
    vector<DrawableShape> shapes;
public:
    Scene(string name = "Untitiled scene");

    void addShape(DrawableShape& shape);
    void addShape(shared_ptr<Shape> shape, string name, int id=-1);

    void removeShapeById(int id);
    void exportToOBJ(string filename = "untitled-scene.obj");

    string getName();
    vector<DrawableShape> getShapes();

    // Extra methods (just for interactive building, maybe removed later)
    void createInteractiveScene();
    void listShapes();
};
