#include<bits/stdc++.h>
using namespace std;

#include "point.cpp"
#include "../gnuplot/gnuplot-utils.cpp"

template <typename T>
class Line {
public:
    T start, end;

    Line(T s, T e) { 
        start = s;
        end = e;
    }

    void draw(){
        GnuplotUtils gp;
        if constexpr(is_same_v<T, Point3D>) {
            vector<tuple<double,double,double>> plotData;
            for(auto& point : {start,end}){
                plotData.push_back(point.toTuple());
            }
            gp.plot3D(plotData);
        } else {
            vector<pair<double,double>> plotData;
            for(auto& point : {start,end}){
                plotData.push_back(point.toPair());
            }
            gp.plot2D(plotData);
        }
    }
};