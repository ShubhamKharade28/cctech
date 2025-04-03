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

Vector computeNormal(Vector v1, Vector v2, Vector v3){
    Vector normal(3);
    
    // Cross product of two edge vectors
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

StlShape getSphereTriangles(double r, int slices = 20, int stacks = 20) {
    double x=0, y=0, z=0;

    StlShape triangles;
    vector<vector<Vector>> points(stacks + 1, vector<Vector>(slices + 1));

    // Generate points on the sphere
    for (int i = 0; i <= stacks; i++) {
        double phi = M_PI * (-0.5 + double(i) / stacks); // Latitude angle (-π/2 to π/2)
        for (int j = 0; j <= slices; j++) {
            double theta = 2 * M_PI * double(j) / slices; // Longitude angle (0 to 2π)
            double px = x + r * cos(phi) * cos(theta);
            double py = y + r * cos(phi) * sin(theta);
            double pz = z + r * sin(phi);
            points[i][j] = {px, py, pz+r};
        }
    }

    // Generate triangles
    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            Vector v1 = points[i][j];
            Vector v2 = points[i + 1][j];
            Vector v3 = points[i][j + 1];
            Vector v4 = points[i + 1][j + 1];

            Vector normal1 = computeNormal(v1, v2, v3);
            Vector normal2 = computeNormal(v2, v4, v3);

            triangles.push_back(Triangle(normal1, v1, v2, v3)); // First triangle
            triangles.push_back(Triangle(normal2, v2, v4, v3)); // Second triangle
        }
    }

    return triangles;
}

void writeSTL(string filename, StlShape& triangles) {
    string filepath = "3d-files" + filename;
    ofstream file(filepath);
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
    cout << "STL file saved: data/" << filename << endl;
}

void writeOBJ(string filename, StlShape& triangles) {
    string filepath = "3d-files/" + filename;
    ofstream file(filepath);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

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
        
        uniqueNormals.push_back(tri.normal);
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

}