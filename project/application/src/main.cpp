#include <bits/stdc++.h>
using namespace std;

#include "geometry.h"
#include "sketcher.h"

void drawSketchUsingInput() {
    Sketcher Robot("Robot", "robot.dat");
    char more = 'y';
    while(more == 'y'){
        cout <<"What shape do you want to draw? " << endl
            << "1. Cuboid" << endl 
            << "2. Sphere" << endl
            << "3. Cylinder" << endl;
        int choice; cin >> choice;

        switch (choice)
        {
        case 1: {
            shared_ptr<Shape> shape = make_shared<Cuboid>();
            shape->input();
            shape->inputTransformation();
            Robot.addShape(shape);
            break;
        }
        case 2: {
            shared_ptr<Shape> shape = make_shared<Sphere>();
            shape->input();
            shape->inputTransformation();
            Robot.addShape(shape);
            break;
        }
        case 3: {
            shared_ptr<Shape> shape = make_shared<Cylinder>();
            shape->input();
            shape->inputTransformation();
            Robot.addShape(shape);
            break;
        }
        default:
            break;
        }

        Robot.draw(5);
        
        cout <<"Add more shapes? (y/n): ";
        cin >> more;
        cout << endl;
    }

    Robot.draw();
}

int main() {
    Sketcher robot("Robot", "robo-v2.dat");

    auto head = make_shared<Sphere>(2, 0, 0, 12.2);  // Sphere with radius 2 at (0,0,10)
    auto neck = make_shared<Cylinder>(1, 2, 0, 0, 8.2);  // Cylinder with radius 1, height 1 at (0,0,8)
    auto body = make_shared<Cuboid>(6, 4, 8, 0, 0, 5);  // Cuboid with length 6, breadth 4, height 6 centered at (0,0,5)

    auto leftHand = make_shared<Cylinder>(1, 5, -7, 0, -1);  // Cylinder with radius 1, height 5 at (-5,1,5), rotated -30 degrees
    auto rightHand = make_shared<Cylinder>(1, 5, 7.2, 0, -1.5);  // Cylinder with radius 1, height 5 at (5,1,5), rotated 30 degrees

    auto leftLeg = make_shared<Cylinder>(1, 4, -2, 0, -2);  // Cylinder with radius 1, height 4 at (-2,0,1)
    auto rightLeg = make_shared<Cylinder>(1, 4, 2, 0, -2);  // Cylinder with radius 1, height 4 at (2,0,1)

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
    

    return 0;
}
