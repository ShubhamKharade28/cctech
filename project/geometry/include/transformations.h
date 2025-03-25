#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>
using namespace std;

#define vvd vector<vector<double>>

class Transformations {
private:
    vvd multiplyMatrix(const vvd &A, const vvd &B); // Matrix multiplication

public:
    vvd X; // Stores the shape points
    Transformations(const vvd &X); // Constructor

    vvd rotate(double angle, vector<double> pivot = {});  // Rotation
    vvd scale(double scaleFactor, vector<double> pivot = {});  // Scaling
    vvd translate(double dx, double dy);  // Translation
};

#endif
