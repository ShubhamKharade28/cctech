#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"

int main(){
    Point3D start(0,0,0), end(10,20,30);
    Line<Point3D> line(start, end);
    line.draw();
}

