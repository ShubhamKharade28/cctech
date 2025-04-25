#pragma once
#include "sketcher_primitives.h"

enum primitiveType {
    VERTEX,
    EDGE,
    FACE,
    SOLID
};

class Sketcher {
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    vector<Face*> faces;
    vector<Solid*> solids;

    // TODO: for future use (selection purpose)
    int currentVertexIdx = 0;
    int currentEdgeIdx = 0;
    int currentFaceIdx = 0;
    int currentSolidIdx = 0;

public:
    Sketcher() {}
    ~Sketcher(); 

    void addVertex(double x, double y, double z);
    void removeVertex(double x, double y, double z);
    void removeVertex(Vertex* vertex);
    void removeVertex(int vertexIdxvoid);

    void addEdge(Vertex* start, Vertex* end);
    void addEdge(int startIdx, int endIdx);
    void removeEdge(Vertex* start, Vertex* end);
    void removeEdge(Edge* edge);
    void removeEdge(int edgeIdx);

    void addFace();
    void addFace(vector<Edge*> edges);
    void removeFace(int faceIdx);
    void removeFace(Face* face);

    void addSolid();
    void addSolid(vector<Face*> faces);
    void removeSolid(int solidIdx);
    void removeSolid(Solid* solid);

    vector<Vertex*> getVertices() { return vertices; }
    vector<Edge*> getEdges() { return edges; }
    vector<Face*> getFaces() { return faces; }
    vector<Solid*> getSolids() { return solids; }
};