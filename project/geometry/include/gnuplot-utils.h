#ifndef GNUPLOT_UTILS_H
#define GNUPLOT_UTILS_H

#include "gnuplot-iostream.h"
#include <bits/stdc++.h>

#define pd pair<double, double>
#define td tuple<double, double, double>

using namespace std;

class GnuplotUtils {
public:
    void plot2D(vector<pd>& plotData, string title = "2D Line");
    void plot3D(vector<td>& plotData, string title = "3D Line");

    void save2D(vector<pd>& plotData, string filename);
    void open2D(string dataFile, string title);
    void draw2D(vector<pd>& plotData, string filename, string title);

    void save3D(vector<td>& plotData, string filename);
    void open3D(string dataFile, string title);
    void draw3D(vector<td>& plotData, string filename, string title);

};

#endif
