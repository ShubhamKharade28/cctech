#ifndef SKETCHER_H
#define SKETCHER_H

#include <vector>
#include <memory>
#include "geometry.h"  // Include the base Shape class

class Sketcher {
private:
    vector<shared_ptr<Shape>> shapes;  // Store shapes as shared pointers

public:
    // Add a shape to the sketcher
    void addShape(shared_ptr<Shape> shape);

    // Get the drawable representation of all shapes
    vvd getDrawable();

    void draw();

    // Destructor (default)
    ~Sketcher() = default;
};

#endif // SKETCHER_H
