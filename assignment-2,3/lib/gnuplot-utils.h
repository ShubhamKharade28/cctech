#ifndef GNUPLOT_UTILS_H
#define GNUPLOT_UTILS_H

#include "gnuplot-iostream.h"
#include <bits/stdc++.h>

using namespace std;

class GnuplotUtils {
public:
    void plot2D(vector<pair<double, double>>& plotData, string title = "2D Line");
    void plot3D(vector<tuple<double, double, double>>& plotData, string title = "3D Line");
};

#endif
