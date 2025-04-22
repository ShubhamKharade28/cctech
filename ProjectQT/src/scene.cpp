#include "scene.h"
#include "threed-utils.h"
#include "file-utils.h"
#include "shapes.h"
#include <iomanip>

Scene::Scene(string name) : name(name) {}

void Scene::addShape(DrawableShape& shape){
    shapes.push_back(shape);
}

void Scene::addShape(shared_ptr<Shape> shape, string name, int id) {
    if(id==-1) {
        if(shapes.empty()) 
            id = 0;
        else
            id = shapes[shapes.size()-1].getId() + 1;
    }
    DrawableShape drawableShape(shape, name, id);
    addShape(drawableShape);
}

void Scene::removeShapeById(int id){
    shapes.erase(remove_if(shapes.begin(), shapes.end(), 
        [&id](DrawableShape& s) { 
            return s.getId() == id;
        }), 
        shapes.end());
}

void Scene::exportToOBJ(string filename) {
    StlShape allTriangles;

    for (auto& drawable : shapes) {
        StlShape tris = drawable.getTriangles(); // Already transformed
        allTriangles.insert(allTriangles.end(), tris.begin(), tris.end());
    }

    FileUtils::writeOBJ(filename, allTriangles);
    cout << "Scene exported to OBJ: " << filename << endl;
    cout << "Total faces (triangles): " << allTriangles.size() << endl;
}

string Scene::getName() { return name; }

vector<DrawableShape>& Scene::getDrawableShapes() {
    return shapes;
}

shared_ptr<Shape> chooseShape(int i) {
    static unordered_map<int, function<shared_ptr<Shape>()>> shapeFactory = {
        {1, [] { return make_shared<Cuboid>(); }},
        {2, [] { return make_shared<Sphere>(); }},
        {3, [] { return make_shared<Cylinder>(); }}
    };

    return shapeFactory.count(i) ? shapeFactory[i]() : nullptr;
}

DrawableShape* Scene::getShapeById(int id) {
    auto it = find_if(shapes.begin(), shapes.end(), [id](DrawableShape& shape) {
        return shape.getId() == id;
    });

    if (it != shapes.end()) 
        return &(*it);
    else 
        return nullptr;
}