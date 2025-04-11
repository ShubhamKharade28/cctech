#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "threed-utils.h"
#include "scene.h"

int main() {
    Scene scene("test-scene");

    auto cuboid = make_shared<Cuboid>(40, 40, 60);
    auto cylinder = make_shared<Cylinder>(20, 100);

    DrawableShape drawableCuboid(cuboid, "my-cuboid", 1);
    DrawableShape drawableCylinder(cylinder, "my-cylinder", 3);

    drawableCuboid.setTranslation({0,0,100});

    scene.addShape(drawableCuboid);
    scene.addShape(drawableCylinder);

    scene.listShapes();
    scene.exportToOBJ("data/Cuboid&Cylinder.obj");
}
