#pragma once 

#include <bits/stdc++.h>
using namespace std;

class Vertex {
    int id;
    double x, y, z;
public:
    Vertex(int id, double x, double y, double z) : id(id), x(x), y(y), z(z) {}
    int getId() const { return id; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }
};

class Edge {
    int id;
    Vertex* start;
    Vertex* end;
public:
    Edge(int id, Vertex* start, Vertex* end) : id(id), start(start), end(end) {}
    int getId() const { return id; }
    Vertex* getStart() const { return start; }
    Vertex* getEnd() const { return end; }
    void setStart(Vertex* start) { this->start = start; }
    void setEnd(Vertex* end) { this->end = end; }
};

class Face {
    int id;
    vector<Edge*> edges;
    public:
    Face(int id) : id(id) {}
    int getId() const { return id; }
    void addEdge(Edge* edge) { edges.push_back(edge); }
    vector<Edge*> getEdges() const { return edges; }
};

class Solid {
    int id;
    vector<Face*> faces;
public:
    Solid(int id) : id(id) {}
    int getId() const { return id; }
    void addFace(Face* face) { faces.push_back(face); }
    vector<Face*> getFaces() const { return faces; }
};