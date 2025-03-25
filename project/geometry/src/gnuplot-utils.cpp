
#include "gnuplot-utils.h"
#include "gnuplot-iostream.h"
using namespace std;

#define pd pair<double, double>
#define td tuple<double, double, double>

void GnuplotUtils::plot2D(vector<pd>& plotData, string title) {
    Gnuplot gp;
    gp << "set terminal wxt\n"; 
    gp << "set xlabel 'X'\n";
    gp << "set ylabel 'Y'\n";
    gp << "set title '" << title << "'\n";
    gp << "plot '-' with lines title '2D Line'\n";
    gp.send1d(plotData);
}

void GnuplotUtils::plot3D(vector<td>& plotData, string title) {
    Gnuplot gp;
    gp << "set terminal wxt\n";
    gp << "set xlabel 'X'\n";
    gp << "set ylabel 'Y'\n";
    gp << "set zlabel 'Z'\n";
    gp << "set title '" << title << "'\n";
    gp << "splot '-' with lines title '3D Line'\n";
    gp.send1d(plotData);
}

void GnuplotUtils::save2D(vector<pd>& plotData, string filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (auto& point : plotData) {
        file << point.first << " " << point.second << "\n";
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

void GnuplotUtils::draw2D(vector<pd>& plotData, string filename, string title) {
    string filepath = "data/" + filename;
    save2D(plotData, filepath);
    open2D(filepath, title);
}

void GnuplotUtils::save3D(vector<td>& plotData, string filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (const auto& point : plotData) {
        file << get<0>(point) << " " << get<1>(point) << " " << get<2>(point) << "\n";
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

void GnuplotUtils::draw3D(vector<td>& plotData, string filename, string title) {
    string filepath = "data/" + filename;
    save3D(plotData, filepath);
    open3D(filepath, title);
}