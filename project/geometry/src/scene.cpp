#include "scene.h"
#include "threed-utils.h"
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

        auto drawable = DrawableShape(shape, name, id++);
        drawable.setTranslation({tx, ty, tz});
        drawable.setScale(scale);
        drawable.setRotation({rx, ry, rz});

        addShape(drawable);

        cout << "Shape added successfully!\n";
    }
}

void Scene::listShapes() {
    if (shapes.empty()) {
        cout << "No shapes in the scene." << endl;
        return;
    }

    // Print header
    cout << left << setw(5) << "ID"
         << setw(15) << "Name"
         << setw(12) << "Type"
         << setw(20) << "Color (R,G,B)"
         // << setw(25) << "Translation (X,Y,Z)"
         // << setw(25) << "Rotation (X,Y,Z)"
         // << setw(8) << "Scale"
         << endl;

    cout << string(60, '-') << endl;

    // Print shape data
    for (auto& shape : shapes) {
        Vector color = shape.getColor();
        // Vector t = shape.getTranslation();
        // Vector r = shape.getRotation();

        cout << left << setw(5) << shape.getId()
             << setw(15) << shape.getName()
             << setw(12) << shape.getType()
             << setw(20) << ("(" + to_string(color[0]) + ", " + to_string(color[1]) + ", " + to_string(color[2]) + ")")
             // << setw(25) << ("(" + to_string(t[0]) + ", " + to_string(t[1]) + ", " + to_string(t[2]) + ")")
             // << setw(25) << ("(" + to_string(r[0]) + ", " + to_string(r[1]) + ", " + to_string(r[2]) + ")")
             // << setw(8) << shape.getScale()
             << endl;
    }
}