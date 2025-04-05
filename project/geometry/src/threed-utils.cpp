#include "threed-utils.h"

#include <bits/stdc++.h>
using namespace std;

Triangle::Triangle(Vector n, Vector v1, Vector v2, Vector v3): 
    normal(n), vertex1(v1), vertex2(v2), vertex3(v3) {}

// Read STL file and convert to a list of triangles
StlShape ThreeDUtils::readSTL(string& filename) {
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
    ofstream file(filename);
    int index = 1;
    for (auto& tri : triangles) {
        file << "v " << tri.vertex1[0] << " " << tri.vertex1[1] << " " << tri.vertex1[2] << "\n";
        file << "v " << tri.vertex2[0] << " " << tri.vertex2[1] << " " << tri.vertex2[2] << "\n";
        file << "v " << tri.vertex3[0] << " " << tri.vertex3[1] << " " << tri.vertex3[2] << "\n";
    }
    for (size_t i = 0; i < triangles.size(); ++i) {
        file << "f " << index << " " << index + 1 << " " << index + 2 << "\n";
        index += 3;
    }
    cout << "OBJ file saved: " << filename << endl;
}

// Compute the normal for a triangle
Vector ThreeDUtils::computeNormal(Vector v1, Vector v2, Vector v3) {
    Vector normal(3);
    normal[0] = (v2[1] - v1[1]) * (v3[2] - v1[2]) - (v2[2] - v1[2]) * (v3[1] - v1[1]);
    normal[1] = (v2[2] - v1[2]) * (v3[0] - v1[0]) - (v2[0] - v1[0]) * (v3[2] - v1[2]);
    normal[2] = (v2[0] - v1[0]) * (v3[1] - v1[1]) - (v2[1] - v1[1]) * (v3[0] - v1[0]);
    return normal;
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