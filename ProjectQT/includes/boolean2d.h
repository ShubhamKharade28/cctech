#pragma once 

#include "sketcher_primitives.h"
#include <vector>

#define pdd pair<double, double>

enum BooleanType {
    Union, 
    Difference,
    Intersection
};

class Sketcher;

class Boolean2D {
public:
    static Face* perform(Face* faceA, Face* faceB, BooleanType op, Sketcher* sketcher);
    static Face* intersect(Face* faceA, Face* B, Sketcher* sketcher);
    static Face* difference(Face* faceA, Face* B, Sketcher* sketcher);
    static Face* unify(Face* faceA, Face* B, Sketcher* sketcher);

private:
    static vector<pdd> to2DPolygon(Face* face);
    static Face* from2DPolygon(vector<pdd>& polygon, Sketcher* sketcher);

    static bool edgesIntersect(pdd& a1, pdd& a2, pdd& b1, pdd& b2);
    static vector<pdd> getIntersectingPoints(vector<pdd>& polyA, vector<pdd>& polyB);
    static vector<pdd> combine(vector<pdd> path1, vector<pdd> path2);
    static map<string, vector<pdd>> getBooleanPaths(vector<pdd>& polyA, vector<pdd>& polyB, vector<pdd>& intersectionPoints);
};