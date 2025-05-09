#pragma once 

#include "sketcher_primitives.h"
#include "sketcher.h"
#include <vector>

enum class BooleanType {
    Union, 
    Difference,
    Intersection
};

class Boolean2D {
public:
    static Face* perform(Face* faceA, Face* faceB, BooleanType op, Sketcher* sketcher);

private:
    static Face* intersect(Face* faceA, Face* B, Sketcher* sketcher);
    static Face* difference(Face* faceA, Face* B, Sketcher* sketcher);
    static Face* unify(Face* faceA, Face* B, Sketcher* sketcher);

    static vector<pair<double, double>> to2DPolygon(Face* face);
    static Face* from2DPolygon(vector<pair<double, double>>& polygon, Sketcher* sketcher);
};