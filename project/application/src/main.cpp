#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"

int main(){
    cout << "In what dimensions do you want to draw?" << endl 
        << "\t 1. 2D" << endl
        << "\t 2. 3D" << endl;

    int c = 1; cin >> c;

    if(c==1) { // 2D diagrams
        cout <<"What do you want to draw?" << endl
            << "\t 1. Line" << endl
            << "\t 2. Rectangle" << endl
            << "\t 3. Square" << endl
            << "\t 4. Circle" << endl
            << "\t 5. Triangle" << endl;

        cin >> c;
        switch (c)
        {
            case 1:
                cout <<"Drawing a line..." << endl;
                break;
            case 2: {
                Rectangle rg;
                rg.input();
                rg.draw();
                cout <<"Drawing a rectangle..." << endl;
                break;
            }
            default:
                break;
        }
    } 
    else { // 3D diagrams
        cout <<"What do you want to draw?" << endl
            << "\t 1. Cuboid" << endl 
            << "\t 2. Cube" << endl 
            << "\t 3. Sphere" << endl
            << "\t 4. Cylinder" << endl;
        
        cin >> c;
        switch (c)
        {
        case 1:
            cout << "Drawing a cuboid...";
            break;
        case 2:
            cout << "Drawing a cube...";
            break;
        default:
            break;
        }
    }
}

