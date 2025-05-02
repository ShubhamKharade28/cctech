#include "mainwindow.h"

#include <QWidget>

#include "scene_creator.h"
#include "bezier_sketcher.h"
#include "sketcher_screen.h"
#include "mainscreen.h"

#include "screen_selector_dialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ScreenSelectorDialog selectorDialog(this);
    if(selectorDialog.exec() == QDialog::Accepted) {
        int selectedScreen = selectorDialog.getSelectedScreen();
        showScreen(selectedScreen);
    } else {
        close();
    }
}

MainWindow::~MainWindow() {}

// void MainWindow::showSceneCreatorScreen() {
//     this->resize(1000, 700);
//     setWindowTitle("Project 3D");

//     SceneCreator *sceneCreator = new SceneCreator(this);
//     setCentralWidget(sceneCreator);
// }
// void MainWindow::showBezierCurveScreen() {
//     this->resize(1000, 700);
//     setWindowTitle("Test - Bezier Curve");

//     BezierSketcher *bezierSketcher = new BezierSketcher(this);
//     setCentralWidget(bezierSketcher);
// }

// void MainWindow::showSketcherScreen() {
//     this->resize(1000, 700);
//     setWindowTitle("Test - Sketcher");

//     SketcherScreen *sketcherScreen = new SketcherScreen(this);
//     setCentralWidget(sketcherScreen);
// }

void MainWindow::showScreen(int screenIndex) {
    this->resize(1000, 700);
    QWidget* screen = nullptr;
    
    switch(screenIndex) {
        case 0:
            setWindowTitle("Scene Creator");
            screen = new SceneCreator(this);
            break;
        case 1:
            setWindowTitle("Bezier Curve");
            screen = new BezierSketcher(this);
            break;
        case 2:
            setWindowTitle("Sketcher");
            screen = new SketcherScreen(this);
            break;
        case 3:
            setWindowTitle("Main Screen");
            screen = new MainScreen(this);
            break;
        default:
            setWindowTitle("Invalid Screen");
            break;
    }

    if(screen) {
        setCentralWidget(screen);
    } else {
        setWindowTitle("Error: Screen not found");
    }
}