#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <bits/stdc++.h>
using namespace std;

#define vvd vector<vector<double>>

class Transformations {
private:
    vvd multiplyMatrix(vvd &A, vvd &B);
    vvd toCartesian(vvd& points);
    vvd toHomogeneous(vvd& points);
public:
    vvd translate(vvd& X, double dx, double dy, double dz); 
    vvd rotate(vvd& X, double angle, char axis, vector<double> pivot = {}); 
    vvd scale(vvd& X, double scaleFactor, vector<double> pivot = {});
};

#endif
