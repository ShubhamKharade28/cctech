#include<bits/stdc++.h>
using namespace std;

class Point {
public:
    double x,y;
    Point(){ 
        x=0;
        y=0;
    } 
    Point(double x, double y){
        this->x = x;
        this->y = y;
    }
    
    pair<double,double> toPair(){
        return {x,y};
    }
};

class Point3D: public Point {
public:
    double z;
    Point3D(){
        z = 0;
    }
    Point3D(double x, double y, double z): Point(x,y) {
        this->z = z;
    }

    tuple<double,double,double> toTuple() const{
        return {x,y,z};
    }
};