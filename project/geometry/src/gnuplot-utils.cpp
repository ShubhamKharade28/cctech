
#include "gnuplot-utils.h"
#include "gnuplot-iostream.h"
using namespace std;

void GnuplotUtils::plot2D(vvd& dataPoints, string title) {
    Gnuplot gp;
    gp << "set terminal wxt\n"; 
    gp << "set xlabel 'X'\n";
    gp << "set ylabel 'Y'\n";
    gp << "set title '" << title << "'\n";
    gp << "plot '-' with lines title '2D Line'\n";
    gp.send1d(dataPoints);
}

void GnuplotUtils::plot3D(vvd& dataPoints, string title) {
    Gnuplot gp;
    // # unfilled
    gp << "set terminal wxt\n";
    gp << "set xlabel 'X'\n";
    gp << "set ylabel 'Y'\n";
    gp << "set zlabel 'Z'\n";
    gp << "set title '" << title << "'\n";
    gp << "splot '-' with lines title '3D Line'\n";

    gp.send1d(dataPoints);
}

void GnuplotUtils::plotCurve(vvd& dataPoints, string title) {
    Gnuplot gp;
    gp << "set terminal wxt\n";
    gp << "set xlabel 'X'\n";
    gp << "set ylabel 'Y'\n";
    gp << "set zlabel 'Z'\n";
    gp << "set title '" << title << "'\n";
    gp << "splot '-' using 1:2:3 smooth csplines with lines title 'Bezier Curve'\n";  
    gp.send1d(dataPoints);
}

void GnuplotUtils::save2D(vvd& dataPoints, string filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (auto& point : dataPoints) {
        file << point[0] << " " << point[1] << "\n";
    }
    file.close();
}

void GnuplotUtils::open2D(const string dataFile, string title) {
    ofstream script("plot_2d.gnu");
    if (!script) {
        cerr << "Error creating Gnuplot script!" << endl;
        return;
    }
    script << "set terminal wxt\n"
           << "set xlabel 'X'\n"
           << "set ylabel 'Y'\n"
           << "set title '" << title << "'\n"
           << "plot '" << dataFile << "' with lines title '2D Plot'\n";
    script.close();
    system("gnuplot -persist plot_2d.gnu");
}

void GnuplotUtils::draw2D(vvd& dataPoints, string filename, string title) {
    string filepath = "data/" + filename;
    save2D(dataPoints, filepath);
    open2D(filepath, title);
}

void GnuplotUtils::save3D(vvd& dataPoints, string filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (auto& point : dataPoints) {
        file << point[0] << " " << point[1] << " " << point[2] << "\n";
    }
    file.close();
}

void GnuplotUtils::open3D(string dataFile, string title) {
    ofstream script("plot_3d.gnu");
    if (!script) {
        cerr << "Error creating Gnuplot script!" << endl;
        return;
    }
    script << "set terminal wxt\n"
           << "set xlabel 'X'\n"
           << "set ylabel 'Y'\n"
           << "set zlabel 'Z'\n"
           << "set title '" << title << "'\n"
           << "splot '" << dataFile << "' with lines title '3D Plot'\n";
    script.close();
    system("gnuplot -persist plot_3d.gnu");
}

void GnuplotUtils::draw3D(vvd& dataPoints, string filename, string title) {
    string filepath = "data/" + filename;
    save3D(dataPoints, filepath);
    open3D(filepath, title);
}