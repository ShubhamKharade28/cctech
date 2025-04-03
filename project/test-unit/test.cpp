#include <bits/stdc++.h>
using namespace std;

#include "utils.cpp"

int main(){
    // double r; cin >> r;

    double r = 10;

    string filename = "mysphere.obj";
    StlShape sphere = getSphereTriangles(r);
    writeOBJ(filename, sphere);
}
