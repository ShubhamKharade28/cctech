#include "scene.h"

Scene::Scene(string name) : name(name) {}

void Scene::addShape(DrawableShape& shape){
    shapes.push_back(shape);
}

void Scene::addShape(shared_ptr<Shape> shape, string name, int id) {
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
    ofstream file(filename);

    if(!file.is_open()) {
        cerr << "Failed to write to file: " << filename << std::endl;
        return;
    }

    int vertexCounter = 1;
    for (DrawableShape& shape : shapes) {
        StlShape tris = shape.getTriangles();

        for (Triangle& tri : tris) {
            file << "v " << tri.vertex1[0] << " " << tri.vertex1[1] << " " << tri.vertex1[2] << "\n";
            file << "v " << tri.vertex2[0] << " " << tri.vertex2[1] << " " << tri.vertex2[2] << "\n";
            file << "v " << tri.vertex3[0] << " " << tri.vertex3[1] << " " << tri.vertex3[2] << "\n";
        }
    }

    int totalFaces = 0;
    for (DrawableShape& shape : shapes) {
        StlShape tris = shape.getTriangles();

        for (int i = 0; i < tris.size(); ++i) {
            file << "f " << vertexCounter     << " "
                         << vertexCounter + 1 << " "
                         << vertexCounter + 2 << "\n";
            vertexCounter += 3;
            totalFaces++;
        }
    }

    file.close();
    cout << "OBJ file exported: " << filename << " (" << totalFaces << " faces)" << endl;
}

string Scene::getName() { return name; }

vector<DrawableShape> Scene::getShapes() {
    return shapes;
}