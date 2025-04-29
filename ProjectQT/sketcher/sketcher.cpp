#include "sketcher.h"
#include <QDebug>

Sketcher::~Sketcher() {
    for(auto v : vertices) delete v;
    for(auto e : edges) delete e;
    for(auto f : faces) delete f;
    for(auto s : solids) delete s;
}

void Sketcher::addVertex(double x, double y, double z){
    // check if vertex already exists
    for(auto v : vertices) {
        if(v->getX() == x && v->getY() == y && v->getZ() == z) return;
    }

    Vertex* v = new Vertex(x, y, z);
    vertices.push_back(v);
}

void Sketcher::removeVertex(double x, double y, double z) {
    // delete vertex if it exists
    for(auto it = vertices.begin(); it != vertices.end(); ++it) {
        Vertex* v = *it;
        if(v->getX() == x && v->getY() == y && v->getZ() == z) {
            vertices.erase(it);
            delete v;
            return;
        }
    }
}

void Sketcher::removeVertex(Vertex* vertex) {
    // delete vertex if it exists
    for(auto it = vertices.begin(); it != vertices.end(); ++it) {
        if(*it == vertex) {
            vertices.erase(it);
            delete vertex;
            return;
        }
    }
}

void Sketcher::removeVertex(int vertexIdx) {
    if(vertexIdx < 0 || vertexIdx >= vertices.size()) return;
    Vertex* v = vertices[vertexIdx];
    vertices.erase(vertices.begin() + vertexIdx);
    delete v;
}


/* Methods for adding and removing a Edge in sketch */
void Sketcher::addEdge(Vertex* start, Vertex* end) {
    for(auto e : edges) {
        if(e->getStart() == start && e->getEnd() == end) return;
    }
    Edge* e = new Edge(start, end);
    edges.push_back(e);
}

void Sketcher::addEdge(int startIdx, int endIdx) {
    if(startIdx < 0 || startIdx >= vertices.size() || endIdx < 0 || endIdx >= vertices.size()) return;
    Vertex* start = vertices[startIdx];
    Vertex* end = vertices[endIdx];
    addEdge(start, end);
}

void Sketcher::removeEdge(Vertex* start, Vertex* end) {
    for(auto it = edges.begin(); it != edges.end(); ++it) {
        Edge* e = *it;
        if(e->getStart() == start && e->getEnd() == end) {
            edges.erase(it);
            delete e;
            return;
        }
    }
}

void Sketcher::removeEdge(Edge* edge) {
    for(auto it = edges.begin(); it != edges.end(); ++it) {
        if(*it == edge) {
            edges.erase(it);
            delete edge;
            return;
        }
    }
}

void Sketcher::removeEdge(int edgeIdx) {
    if(edgeIdx < 0 || edgeIdx >= edges.size()) return;
    Edge* e = edges[edgeIdx];
    edges.erase(edges.begin() + edgeIdx);
    delete e;
}


// validation for face edges
bool Sketcher::checkFaceEdgesValidity(vector<Edge*>& faceEdges) {
    // check if edges are connected to each other
    for(int i=0; i<faceEdges.size()-1; i++){
        auto e1 = faceEdges[i], e2 = faceEdges[i+1];
        auto v1 = e1->getStart(), v2 = e1->getEnd();
        auto v3 = e2->getStart(), v4 = e2->getEnd();

        if (!(v1 == v3 || v1 == v4 || v2 == v3 || v2 == v4)) {
            return false;
        }
    }

    auto firstEdge = faceEdges[0];
    auto lastEdge = faceEdges[faceEdges.size() - 1];
    auto firstStart = firstEdge->getStart(), firstEnd = firstEdge->getEnd();
    auto lastStart = lastEdge->getStart(), lastEnd = lastEdge->getEnd();

    if (!(firstStart == lastStart || firstStart == lastEnd || firstEnd == lastStart || firstEnd == lastEnd)) {
        return false;
    }

    return true;
}

/* Methods for adding and removing faces in sketches */
void Sketcher::addFace() {
    Face* f = new Face();
    faces.push_back(f);
}

void Sketcher::addFace(vector<Edge*> edges) {
    Face* f = new Face(edges);
    faces.push_back(f);
}

void Sketcher::addFace(vector<int>& edgeIdxs) {
    vector<Edge*> faceEdges;
    for(auto idx : edgeIdxs) {
        if(idx < 0 || idx >= edges.size()) return;
        faceEdges.push_back(edges[idx]);
    }

    bool areEdgesValid = checkFaceEdgesValidity(faceEdges);
    if(!areEdgesValid) {
        qDebug() << "Not valid edges to form a face!";
        return;
    }

    Face* f = new Face(edges);
    faces.push_back(f);
}

void Sketcher::removeFace(int faceIdx) {
    if(faceIdx < 0 || faceIdx >= faces.size()) return;
    Face* f = faces[faceIdx];
    faces.erase(faces.begin() + faceIdx);
    delete f;
}

void Sketcher::removeFace(Face* face) {
    for(auto it = faces.begin(); it != faces.end(); ++it) {
        if(*it == face) {
            faces.erase(it);
            delete face;
            return;
        }
    }
}

/* Methods for adding and removing solids in sketcher */
void Sketcher::addSolid() {
    Solid* s = new Solid();
    solids.push_back(s);
}

void Sketcher::addSolid(vector<Face*> faces) {
    Solid* s = new Solid(faces);
    solids.push_back(s);
}

void Sketcher::removeSolid(int solidIdx) {
    if(solidIdx < 0 || solidIdx >= solids.size()) return;
    Solid* s = solids[solidIdx];
    solids.erase(solids.begin() + solidIdx);
    delete s;
}

void Sketcher::removeSolid(Solid* solid) {
    for(auto it = solids.begin(); it != solids.end(); ++it) {
        if(*it == solid) {
            solids.erase(it);
            delete solid;
            return;
        }
    }
}

int Sketcher::findVertex(Vertex* v) {
    for(int i=0; i<vertices.size(); i++) {
        if(vertices[i] == v) return i;
    }
    return -1;
}

int Sketcher::findEdge(Edge* e) {
    for(int i=0; i<edges.size(); i++) {
        if(edges[i] == e) return i;
    }
    return -1;
}

int Sketcher::findFace(Face* f) {
    for(int i=0; i<faces.size(); i++) {
        if(faces[i] == f) return i;
    }
    return -1;
}

int Sketcher::findSolid(Solid* s) {
    for(int i=0; i<solids.size(); i++) {
        if(solids[i] == s) return i;
    }
    return -1;
}