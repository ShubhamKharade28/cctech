#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "threed-utils.h"
#include "scene.h"

int main() {
    Scene scene("test-scene");

    auto cuboid = make_shared<Cuboid>(40, 40, 60);
    auto cylinder = make_shared<Cylinder>(20, 100);

    scene.addShape(cuboid, "my-cuboid");
    scene.addShape(cylinder, "my-cylinder");

    scene.listShapes();
}
