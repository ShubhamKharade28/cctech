#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "threed-utils.h"
#include "scene.h"

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

    scene.exportToOBJ("mynewscene.obj");
}
