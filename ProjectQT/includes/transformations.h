#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <bits/stdc++.h>
using namespace std;

#include "threed-utils.h"
#include <QMatrix4x4>
#include <QVector4D>

// #define Matrix vector<vector<double>>

class Transformations {
public:
    static Matrix applyTransformations(Matrix& X, vector<double> translation, vector<double> rotation, double scale);
    static StlShape applyTransformations(StlShape& X, vector<double> translation, vector<double> rotation, double scale);

private:
    static QMatrix4x4 getTransformationMatrix(vector<double> translation, vector<double> rotation, double scale);
};

#endif
