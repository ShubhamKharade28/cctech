#include <bits/stdc++.h>
using namespace std;

#define Matrix vector<vector<double>>
#define Vector vector<double>

class Triangle {
public:
    Vector normal;
    Vector vertex1;
    Vector vertex2;
    Vector vertex3;
    Triangle(Vector normal, Vector vertex1, Vector vertex2, Vector vertex3):
        normal(normal), vertex1(vertex1), vertex2(vertex2), vertex3(vertex3) {}
};

#define StlShape vector<Triangle>

void writeSTL(string filename, StlShape& triangles) {
    ofstream file(filename);
    file << "solid MyShape\n";

    for (const auto& tri : triangles) {
        file << "  facet normal " << tri.normal[0] << " " << tri.normal[1] << " " << tri.normal[2] << "\n";
        file << "    outer loop\n";
        file << "      vertex " << tri.vertex1[0] << " " << tri.vertex1[1] << " " << tri.vertex1[2] << "\n";
        file << "      vertex " << tri.vertex2[0] << " " << tri.vertex2[1] << " " << tri.vertex2[2] << "\n";
        file << "      vertex " << tri.vertex3[0] << " " << tri.vertex3[1] << " " << tri.vertex3[2] << "\n";
        file << "    endloop\n";
        file << "  endfacet\n";
    }

    file << "endsolid MyShape\n";
    file.close();
    cout << "STL file saved: " << filename << endl;
}

Vector computeNormal(Vector v1, Vector v2, Vector v3){
    Vector normal(3);
    normal[0] = (v2[1] - v1[1]) * (v3[2] - v1[2]) - (v2[2] - v1[2]) * (v3[1] - v1[1]);
    normal[1] = (v2[2] - v1[2]) * (v3[0] - v1[0]) - (v2[0] - v1[0]) * (v3[2] - v1[2]);
    normal[2] = (v2[0] - v1[0]) * (v3[1] - v1[1]) - (v2[1] - v1[1]) * (v3[0] - v1[0]);
    return normal;
}

StlShape getCuboidTriangles(double l, double b, double h){
    StlShape triangles;

    double x=0, y=0, z=0;
    // Matrix vertices = {
    //     {x - l / 2, y - b / 2, z - h / 2}, // 0: Bottom-Left-Back
    //     {x + l / 2, y - b / 2, z - h / 2}, // 1: Bottom-Right-Back
    //     {x + l / 2, y + b / 2, z - h / 2}, // 2: Top-Right-Back
    //     {x - l / 2, y + b / 2, z - h / 2}, // 3: Top-Left-Back
    //     {x - l / 2, y - b / 2, z + h / 2}, // 4: Bottom-Left-Front
    //     {x + l / 2, y - b / 2, z + h / 2}, // 5: Bottom-Right-Front
    //     {x + l / 2, y + b / 2, z + h / 2}, // 6: Top-Right-Front
    //     {x - l / 2, y + b / 2, z + h / 2}  // 7: Top-Left-Front
    // };

    Matrix vertices = {
        {x, y, z},           // 0: Bottom-Left-Back
        {x + l, y, z},       // 1: Bottom-Right-Back
        {x + l, y + b, z},   // 2: Top-Right-Back
        {x, y + b, z},       // 3: Top-Left-Back
        {x, y, z + h},       // 4: Bottom-Left-Front
        {x + l, y, z + h},   // 5: Bottom-Right-Front
        {x + l, y + b, z + h}, // 6: Top-Right-Front
        {x, y + b, z + h}    // 7: Top-Left-Front
    };
    

    Matrix faces = {
        {0, 1, 2}, {0, 2, 3}, // Back face
        {4, 6, 5}, {4, 7, 6}, // Front face
        {0, 3, 7}, {0, 7, 4}, // Left face
        {1, 5, 6}, {1, 6, 2}, // Right face
        {3, 2, 6}, {3, 6, 7}, // Top face
        {0, 4, 5}, {0, 5, 1}  // Bottom face
    };

    for(auto& f : faces){
        Vector v1 = vertices[f[0]], v2 = vertices[f[1]], v3 = vertices[f[2]];
        Vector normal = computeNormal(v1, v2, v3);
        Triangle tri(normal, v1, v2, v3);
        triangles.push_back(tri);
    }

    return triangles;
}

int main(){
    double l,b,h;
    cin >> l >> b >> h;

    string filename = "cuboid.stl";
    StlShape cuboid = getCuboidTriangles(l,b,h);
    writeSTL(filename, cuboid);
}