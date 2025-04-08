#include "scene.h"
#include "threed-utils.h"

Scene::Scene(string name) : name(name) {}

void Scene::addShape(DrawableShape& shape){
    shapes.push_back(shape);
}

void Scene::addShape(shared_ptr<Shape> shape, string name, int id) {
    if(id==-1) {
        id == shapes[shapes.size()-1]->id + 1;
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

    ThreeDUtils::writeOBJ(filename, allTriangles);
    cout << "Scene exported to OBJ: " << filename << endl;
    cout << "Total faces (triangles): " << allTriangles.size() << endl;
}

string Scene::getName() { return name; }

vector<DrawableShape> Scene::getShapes() {
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

void Scene::createInteractiveScene() {
    int choice;
    string name;
    double tx = 0, ty = 0, tz = 0;
    double scale;
    double rx = 0, ry = 0, rz = 0;

    int id=0;

    while (true) {
        cout << "\nChoose a shape to add:\n";
        cout << "1. Cuboid\n2. Sphere\n3. Cylinder\n0. Exit\n> ";
        cin >> choice;

        if (choice == 0) break;

        auto shape = chooseShape(choice);
        if (!shape) {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        cout << "Enter a name for the shape: ";
        cin >> name;

        shape->input();

        cout << "Enter translation (tx ty tz): ";
        cin >> tx >> ty >> tz;

        cout << "Enter scaling: ";
        cin >> scale;

        cout << "Enter rotation (rx ry rz in degrees): ";
        cin >> rx >> ry >> rz;

        auto drawable = DrawableShape(shape, name, id);
        drawable.setTranslation({tx, ty, tz});
        drawable.setScale(scale);
        drawable.setRotation({rx, ry, rz});

        addShape(drawable);

        cout << "Shape added successfully!\n";
    }
}
