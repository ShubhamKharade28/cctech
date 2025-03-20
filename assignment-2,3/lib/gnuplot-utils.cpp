#include "gnuplot-iostream.h"
#include <bits/stdc++.h>
using namespace std;

class GnuplotUtils {
    public:
    void plot2D(vector<pair<double,double>>& plotData, string title = "2D Line") {
        Gnuplot gp;
        gp << "set terminal wxt\n"; 
        gp << "set xlabel 'X'\n";
        gp << "set ylabel 'Y'\n";
        gp << "set title '" << title << "'\n";
        gp << "plot '-' with lines title '2D Line'\n";
        gp.send1d(plotData);
    }

    void plot3D(vector<tuple<double,double,double>>& plotData, string title = "3D Line") {
        Gnuplot gp;
        gp << "set terminal wxt\n";
        gp << "set xlabel 'X'\n";
        gp << "set ylabel 'Y'\n";
        gp << "set zlabel 'Z'\n";
        gp << "set title '" << title << "'\n";
        gp << "splot '-' with lines title '3D Line'\n";
        gp.send1d(plotData);
    }

};