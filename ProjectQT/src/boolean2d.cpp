#include "boolean2d.h"
using namespace std;

Face* Boolean2D::perform(Face* faceA, Face* faceB, BooleanType op, Sketcher* sketcher = nullptr) {
    switch (op) {
        case BooleanType::Union:
            return unify(faceA, faceB, sketcher);
        case BooleanType::Intersection:
            return intersect(faceA, faceB, sketcher);
        case BooleanType::Difference:
            return difference(faceA, faceB, sketcher);
        default:
            return nullptr;
    }
}

Face* Boolean2D::intersect(Face* faceA, Face* faceB, Sketcher* sketcher) {
    auto polyA = to2DPolygon(faceA);
    auto polyB = to2DPolygon(faceB);
    return nullptr;
}

Face* Boolean2D::difference(Face* faceA, Face* faceB, Sketcher* sketcher) {
    auto polyA = to2DPolygon(faceA);
    auto polyB = to2DPolygon(faceB);

    return nullptr;
}

Face* Boolean2D::unify(Face* faceA, Face* faceB, Sketcher* sketcher) {
    auto polyA = to2DPolygon(faceA);
    auto polyB = to2DPolygon(faceB);
    
    return nullptr;
}

vector<pair<double, double>> Boolean2D::to2DPolygon(Face* face) {
    vector<pair<double, double>> polygon;
    for (Vertex* v : face->getVertices()) {
        polygon.emplace_back(v->getX(), v->getY());
    }
    return polygon;
}

Face* Boolean2D::from2DPolygon(vector<pair<double,double>>& polygon, Sketcher* sketcher) {
    if (polygon.size() < 3) return nullptr;

    vector<Vertex*> vertices;
    vector<Edge*> edges;

    for (auto& p : polygon) {
        Vertex* v = sketcher->addVertex(p.first, p.second, 0.0); // z = 0
        vertices.push_back(v);
    }

    for (size_t i = 0; i < vertices.size(); ++i) {
        Vertex* start = vertices[i];
        Vertex* end = vertices[(i + 1) % vertices.size()];
        Edge* e = sketcher->addEdge(start, end);
        edges.push_back(e);
    }

    Face* f = sketcher->addFace(edges);
    return f;
}