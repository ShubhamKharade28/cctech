#ifndef GNUPLOT_UTILS_H
#define GNUPLOT_UTILS_H

#include "gnuplot-iostream.h"
#include <bits/stdc++.h>

#define vvd vector<vector<double>>

using namespace std;
 
class GnuplotUtils {
public:
    void plot2D(vvd& dataPoints, string title = "2D Line");
    void plot3D(vvd& dataPoints, string title = "3D Line");
    void plotCurve(vvd& dataPoints, string title = "Smooth Cuve");

    void save2D(vvd& dataPoints, string filename);
    void open2D(string dataFile, string title);
    void draw2D(vvd& dataPoints, string filename, string title);

    void save3D(vvd& dataPoints, string filename);
    void open3D(string dataFile, string title);
    void draw3D(vvd& dataPoints, string filename, string title);

    void drawTest(vvd& dataPoints);


};

#endif
