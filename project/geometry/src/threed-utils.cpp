#include "threed-utils.h"
#include "geometry.h"
#include <chrono>

#include <bits/stdc++.h>
using namespace std;

Vector substract(Vector a, Vector b){
    return {a[0]-b[0], a[1]-b[1], a[2]-b[2]};
}

Vector cross(Vector a, Vector b){
    return {
        a[1]*b[2] - a[2]*b[1],
        a[2]*b[0] - a[0]*b[2],
        a[0]*b[1] - a[1]*b[0]
    };
}

double magnitude(Vector v) {
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

Vector normalize(Vector v) {
    double mag = magnitude(v);
    if (mag == 0) return {0, 0, 0}; // avoid division by zero
    return {v[0]/mag, v[1]/mag, v[2]/mag};
}

Vector Triangle::getNormal() {
    Vector edge1 = substract(vertex2, vertex1);
    Vector edge2 = substract(vertex3, vertex1);
    return normalize(cross(edge1, edge2));
}

// Compute the normal for a triangle
Vector ThreeDUtils::computeNormal(Vector v1, Vector v2, Vector v3) {
    Vector edge1 = substract(v2, v1);
    Vector edge2 = substract(v3, v1);
    return normalize(cross(edge1, edge2));
}

Triangle::Triangle(Vector n, Vector v1, Vector v2, Vector v3): 
    normal(n), vertex1(v1), vertex2(v2), vertex3(v3) {}

// Read STL file and convert to a list of triangles
StlShape ThreeDUtils::readSTL(string& filename) {
    auto start_time = chrono::high_resolution_clock::now();

    ifstream file(filename);
    StlShape triangles;
    string line;
    Vector normal(3), v1(3), v2(3), v3(3);

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        ss >> token;

        if (token == "facet") {
            ss >> token >> normal[0] >> normal[1] >> normal[2];
        } else if (token == "vertex") {
            ss >> v1[0] >> v1[1] >> v1[2];
            getline(file, line);
            stringstream ss2(line);
            ss2 >> token >> v2[0] >> v2[1] >> v2[2];
            getline(file, line);
            stringstream ss3(line);
            ss3 >> token >> v3[0] >> v3[1] >> v3[2];
            triangles.emplace_back(normal, v1, v2, v3);
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time_taken = end_time - start_time;

    cout <<"STL file read complete: "<< filename << endl;
    cout <<"Triangles read: " << triangles.size() << endl;
    cout <<"Time taken to read: " << time_taken.count() << "seconds" << endl;
    return triangles;
}

// Write STL file from a list of triangles
void ThreeDUtils::writeSTL(string& filename, StlShape& triangles) {
    ofstream file(filename);
    file << "solid MyShape\n";

    for (auto& tri : triangles) {
        file << "  facet normal " << tri.normal[0] << " " << tri.normal[1] << " " << tri.normal[2] << "\n";
        file << "    outer loop\n";
        file << "      vertex " << tri.vertex1[0] << " " << tri.vertex1[1] << " " << tri.vertex1[2] << "\n";
        file << "      vertex " << tri.vertex2[0] << " " << tri.vertex2[1] << " " << tri.vertex2[2] << "\n";
        file << "      vertex " << tri.vertex3[0] << " " << tri.vertex3[1] << " " << tri.vertex3[2] << "\n";
        file << "    endloop\n";
        file << "  endfacet\n";
    }
    file << "endsolid MyShape\n";
    cout << "STL file saved: " << filename << endl;
}

// Read DAT file and convert to triangles
StlShape ThreeDUtils::readDAT(string& filename) {
    ifstream file(filename);
    StlShape triangles;
    Vector v1(3), v2(3), v3(3);

    while (file >> v1[0] >> v1[1] >> v1[2] >> v2[0] >> v2[1] >> v2[2] >> v3[0] >> v3[1] >> v3[2]) {
        Vector normal = computeNormal(v1, v2, v3);
        triangles.emplace_back(normal, v1, v2, v3);
    }
    return triangles;
}

// Write triangles to DAT file
void ThreeDUtils::writeDAT(string& filename, StlShape& triangles) {
    ofstream file(filename);
    for (auto& tri : triangles) {
        file << tri.vertex1[0] << " " << tri.vertex1[1] << " " << tri.vertex1[2] << " ";
        file << tri.vertex2[0] << " " << tri.vertex2[1] << " " << tri.vertex2[2] << " ";
        file << tri.vertex3[0] << " " << tri.vertex3[1] << " " << tri.vertex3[2] << "\n";
    }
    cout << "DAT file saved: " << filename << endl;
}

// Read OBJ file and convert to triangles
StlShape ThreeDUtils::readOBJ(string& filename) {
    ifstream file(filename);
    vector<Vector> vertices;
    StlShape triangles;
    string line, token;
    Vector v1(3), v2(3), v3(3);

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> token;
        if (token == "v") {
            Vector v(3);
            ss >> v[0] >> v[1] >> v[2];
            vertices.push_back(v);
        } else if (token == "f") {
            int i1, i2, i3;
            ss >> i1 >> i2 >> i3;
            v1 = vertices[i1 - 1];
            v2 = vertices[i2 - 1];
            v3 = vertices[i3 - 1];
            Vector normal = computeNormal(v1, v2, v3);
            triangles.emplace_back(normal, v1, v2, v3);
        }
    }
    return triangles;
}

// Write triangles to OBJ file
void ThreeDUtils::writeOBJ(string& filename, StlShape& triangles) {
    auto start_time = chrono::high_resolution_clock::now();

    ofstream file(filename);
    unordered_map<string, int> vertexIndex;
    Matrix uniqueVertices;
    Matrix uniqueNormals;

    int vertexCounter = 1, normalCounter = 1;

    // write obj header
    file << "# OBJ file generated from StlShape\n\n";
    for(auto& tri : triangles){
        Matrix vertices = {tri.vertex1, tri.vertex2, tri.vertex3};

        for(auto& v : vertices) {
            string key = to_string(v[0]) + " " + to_string(v[1]) + " " + to_string(v[2]);

            if(vertexIndex.find(key) == vertexIndex.end()){
                vertexIndex[key] = vertexCounter++;
                uniqueVertices.push_back(v);
            }
        }

        uniqueNormals.push_back(tri.getNormal());
    }

    // Write unique vertices and normals
    for (auto& v : uniqueVertices) {
        file << "v " << v[0] << " " << v[1] << " " << v[2] << "\n";
    }
    file << "\n";

    for (const auto& n : uniqueNormals) {
        file << "vn " << n[0] << " " << n[1] << " " << n[2] << "\n";
    }
    file << "\n";

    // Write faces
    int normalIndex = 1;
    for (auto& tri : triangles) {
        vector<Vector> vertices = {tri.vertex1, tri.vertex2, tri.vertex3};
        string faceLine = "f";

        for (auto& v : vertices) {
            string key = to_string(v[0]) + " " + to_string(v[1]) + " " + to_string(v[2]);
            int vIndex = vertexIndex[key];
            faceLine += " " + to_string(vIndex) + "//" + to_string(normalIndex);
        }

        file << faceLine << "\n";
        normalIndex++;
    }

    file.close();
    cout << "OBJ file successfully written: " << filename << endl;

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> time_taken = end_time - start_time;

    cout <<"OBJ file write complete: "<< filename << endl;
    cout <<"Time taken to write: " << time_taken.count() << "seconds" << endl;
}

// Conversion methods
void ThreeDUtils::stlToDat(string& stlFile, string& datFile) {
    StlShape triangles = readSTL(stlFile);
    writeDAT(datFile, triangles);
}

void ThreeDUtils::datToStl(string& datFile, string& stlFile) {
    StlShape triangles = readDAT(datFile);
    writeSTL(stlFile, triangles);
}

void ThreeDUtils::stlToObj(string& stlFile, string& objFile) {
    StlShape triangles = readSTL(stlFile);
    writeOBJ(objFile, triangles);
}

void ThreeDUtils::objToStl(string& objFile, string& stlFile) {
    StlShape triangles = readOBJ(objFile);
    writeSTL(stlFile, triangles);
}

void ThreeDUtils::datToObj(string& datFile, string& objFile) {
    StlShape triangles = readDAT(datFile);
    writeOBJ(objFile, triangles);
}

void ThreeDUtils::objToDat(string& objFile, string& datFile) {
    StlShape triangles = readOBJ(objFile);
    writeDAT(datFile, triangles);
}

void ThreeDUtils::exportSTL(Shape* shape, string filename) {
    StlShape triangles = shape->computeTriangles();
    writeSTL(filename, triangles);
}

void ThreeDUtils::exportOBJ(Shape* shape, string filename) {
    StlShape triangles = shape->computeTriangles();
    writeOBJ(filename, triangles);
}