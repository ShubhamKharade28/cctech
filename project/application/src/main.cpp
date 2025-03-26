#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "sketcher.h"

int main() {
    // Create shape objects using shared pointers
    shared_ptr<Shape> cb = make_shared<Cuboid>(10, 10, 10, 20, 40, 60);
    shared_ptr<Shape> cyl = make_shared<Cylinder>(20, 30, 40, 10, 50);
    shared_ptr<Shape> sph = make_shared<Sphere>(20, 20,50, 50);

    Sketcher skt;

    // Add shapes to Sketcher
    skt.addShape(cb);
    skt.addShape(cyl);
    skt.addShape(sph);

    // Get drawable representation
    auto drawable = skt.getDrawable();

    // Optionally, draw the shapes
    skt.draw();

    return 0;
}
