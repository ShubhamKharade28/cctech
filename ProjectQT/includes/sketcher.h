#pragma once
#include "sketcher_primitives.h"
#include "boolean2d.h"

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

    Vertex* addVertex(double x, double y, double z);
    void removeVertex(double x, double y, double z);
    void removeVertex(Vertex* vertex);
    void removeVertex(int vertexIdxvoid);

    Edge* addEdge(Vertex* start, Vertex* end);
    Edge* addEdge(int startIdx, int endIdx);
    void removeEdge(Vertex* start, Vertex* end);
    void removeEdge(Edge* edge);
    void removeEdge(int edgeIdx);

    Face* addFace();
    Face* addFace(vector<Edge*> faceEdges);
    Face* addFace(vector<int>& edgeIdxs);
    void removeFace(int faceIdx);
    void removeFace(Face* face);

    Solid* addSolid(Solid* solid);
    Solid* addSolid(vector<Face*> faces);
    void removeSolid(int solidIdx);
    void removeSolid(Solid* solid);

    vector<Vertex*> getVertices() { return vertices; }
    vector<Edge*> getEdges() { return edges; }
    vector<Face*> getFaces() { return faces; }
    vector<Solid*> getSolids() { return solids; }

    int findVertex(Vertex* v);
    int findEdge(Edge* e);
    int findFace(Face* f);
    int findSolid(Solid* s);
    int findVertex(double x, double y, double z, double radius=0.1);
    bool moveVertex(int vertexIdx, double x, double y, double z);

    // validation methods
    bool checkFaceEdgesValidity(vector<Edge*>& faceEdges);

    // extrusion methods
    Solid* extrudeFace(Face* face, double height);
    Solid* extrudeFace(int faceIdx, double height);

    Solid* revolveFace(Face* face, double angle, int steps);
    Solid* revolveFace(int faceIdx, double angle, int steps);

    Face* performBooleanOperation(Face* face1, Face* face2, BooleanType booleanType);
    int performBooleanOperation(int face1, int face2, BooleanType booleanType);

    void clear();

    bool loadSketchFromFile(const string filename);
    bool loadSketchFromSTL(const string filename);
    bool loadSketchFromOBJ(const string filename);
};