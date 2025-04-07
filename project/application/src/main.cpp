#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "sketcher.h"
#include "threed-utils.h"

shared_ptr<Shape> chooseShape(int i) {
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

        shared_ptr<Shape> shape = chooseShape(choice);

        shape->input();
        shape->inputTransformations();
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

    auto head = make_shared<Sphere>(3); 
    auto neck = make_shared<Cylinder>(1, 3);  
    auto body = make_shared<Cuboid>(5,2,12); 

    auto leftHand = make_shared<Cylinder>(1, 4); 
    auto rightHand = make_shared<Cylinder>(1, 4); 

    auto leftLeg = make_shared<Cylinder>(1, 5); 
    
    auto rightLeg = make_shared<Cylinder>(1, 5);  

    head->setTranslation(0,0,11);

    neck->setTranslation(0,0,7);

    leftHand->setRotation(0, 45, 0);
    leftHand->setTranslation(-4, 0, 2);

    rightHand->setRotation(0, -45, 0);
    rightHand->setTranslation(4, 0, 2);

    leftLeg->setTranslation(-3, 0, -6);
    leftLeg->setRotation(0, 10, 0);
    
    rightLeg->setTranslation(3, 0, -6);
    rightLeg->setRotation(0, -10, 0);

    robot.addShape(head);
    robot.addShape(neck);
    robot.addShape(body); for(int j=0; j<10; j++) robot.addShape(body);
    robot.addShape(leftHand);
    robot.addShape(rightHand);
    robot.addShape(leftLeg);
    robot.addShape(rightLeg);
    
    robot.draw();
}

int main() {
    // Cuboid *cb = new Cuboid(10, 20, 50);
    // cb->exportSTL("mycuboid.stl");

    string dataDir = "data/";
    Cuboid cb(50,40,20);
    ThreeDUtils::exportOBJ(&cb, dataDir + "cuboid.obj");

    return 0;
}
