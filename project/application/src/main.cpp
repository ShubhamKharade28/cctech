#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "sketcher.h"

shared_ptr<Shape> getShape(int i) {
    static unordered_map<int, function<shared_ptr<Shape>()>> shapeFactory = {
        {1, [] { return make_shared<Cuboid>(); }},
        {2, [] { return make_shared<Sphere>(); }},
        {3, [] { return make_shared<Cylinder>(); }}
    };

    return shapeFactory.count(i) ? shapeFactory[i]() : nullptr;
}


void drawSketch() {
    cout << "Enter model name: "; 
    string sketchName; cin >> sketchName;
    Sketcher sketch(sketchName, sketchName+".dat");

    char more = 'y';
    while(more == 'y'){
        cout <<"What shape do you want to draw? " << endl
            << "1. Cuboid" << endl 
            << "2. Sphere" << endl
            << "3. Cylinder" << endl;
        int choice; cin >> choice;

        shared_ptr<Shape> shape = getShape(choice);

        shape->input();
        shape->inputTransformation();
        sketch.addShape(shape);

        while(true){
            sketch.draw(5);
            cout <<"Want to update the translations? (y/n): ";
            char toTranslateAgain = 'n'; cin >> toTranslateAgain;
            if(toTranslateAgain == 'n') break;

            cout <<"Enter axis and value: ";
            char axis; double val;
            cin >> axis >> val;
            shape->addTranslation(axis, val);
        }

        sketch.draw(5);
        
        cout <<"Add more shapes? (y/n): ";
        cin >> more;
        cout << endl;
    }

    sketch.draw();
}

void drawRobot() {
    Sketcher robot("Robot", "robo-v2.dat");

    auto head = make_shared<Sphere>(2, 0); 
    auto neck = make_shared<Cylinder>(1, 2);  
    auto body = make_shared<Cuboid>(6, 4, 8);  

    auto leftHand = make_shared<Cylinder>(1, 5); 
    auto rightHand = make_shared<Cylinder>(1, 5); 

    auto leftLeg = make_shared<Cylinder>(1, 4); 
    auto rightLeg = make_shared<Cylinder>(1, 4);  

    leftHand->setRotation(0, -45, 0);
    rightHand->setRotation(0, 45, 0);

    
    robot.addShape(head);
    robot.addShape(neck);
    robot.addShape(body);
    robot.addShape(leftHand);
    robot.addShape(rightHand);
    robot.addShape(leftLeg);
    robot.addShape(rightLeg);
    
    robot.draw();
}

int main() {
    drawSketch();

    return 0;
}
