#ifndef SKETCHER_H
#define SKETCHER_H

#include <vector>
#include <memory>
#include "geometry.h"

class Sketcher {
private:
    string title = "3D Model";
    string filename = "3d-model.dat";
    vector<shared_ptr<Shape>> shapes;
public:
    Sketcher(string title="3D Model", string filename="3d-model.dat"): title(title), filename(filename) {}
    void addShape(shared_ptr<Shape> shape);
    vvd getDrawable();
    void draw(int seconds=0);

    void setTitle(string title);
    void setFileName(string filename);

    ~Sketcher() = default;
};

#endif
