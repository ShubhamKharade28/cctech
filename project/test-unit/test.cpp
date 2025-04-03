#include <bits/stdc++.h>
using namespace std;

#include "stlutils.cpp"

int main(){
    // double r; cin >> r;

    double r = 10;

    string filename = "mysphere.stl";
    StlShape sphere = getSphereTriangles(r);
    writeSTL(filename, sphere);
}
