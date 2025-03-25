#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
// #include "utils.cpp"

int main(){
    Rectangle rg;
    rg.input();

    Rectangle rotatedRg = rg.rotate90();

    rg.draw();
    rotatedRg.draw();
}

