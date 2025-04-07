#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "threed-utils.h"
#include "scene.h"

shared_ptr<Shape> chooseShape(int i) {
    static unordered_map<int, function<shared_ptr<Shape>()>> shapeFactory = {
        {1, [] { return make_shared<Cuboid>(); }},
        {2, [] { return make_shared<Sphere>(); }},
        {3, [] { return make_shared<Cylinder>(); }}
    };

    return shapeFactory.count(i) ? shapeFactory[i]() : nullptr;
}

int main() {
    Scene scene("test-scene");
    int id=0;

    auto cuboid = make_shared<Cuboid>(40, 40, 60);
    auto cylinder = make_shared<Cylinder>(20, 100);

    scene.addShape(cuboid, "my-cuboid", id++);
    scene.addShape(cylinder, "my-cylinder", id++);

    auto shapes = scene.getShapes();
    for(auto shape : shapes){
        cout << shape.getName() << endl;
    }
}
