#include "mainwindow.h"

#include <QWidget>

#include "scene_creator.h"
#include "bezier_sketcher.h"
#include "sketcher_screen.h"

#include "screen_selector_dialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ScreenSelectorDialog selectorDialog(this);
    if(selectorDialog.exec() == QDialog::Accepted) {
        // 0 for SceneCreator, 1 for BezierCurve
        int screenIdx = selectorDialog.getSelectedScreen();
        switch(screenIdx) {
            case 0:
                showSceneCreatorScreen();
                break;
            case 1:
                showBezierCurveScreen();
                break;
            case 2:
                showSketcherScreen();
                break;
            default:
                setWindowTitle("Invalid Screen");
                break;
        }
    } else {
        close();
    }
}

MainWindow::~MainWindow() {}

void MainWindow::showSceneCreatorScreen() {
    this->resize(1000, 700);
    setWindowTitle("Project 3D");

    SceneCreator *sceneCreator = new SceneCreator(this);
    setCentralWidget(sceneCreator);
}
void MainWindow::showBezierCurveScreen() {
    this->resize(1000, 700);
    setWindowTitle("Test - Bezier Curve");

    BezierSketcher *bezierSketcher = new BezierSketcher(this);
    setCentralWidget(bezierSketcher);
}

void MainWindow::showSketcherScreen() {
    this->resize(1000, 700);
    setWindowTitle("Test - Sketcher");

    SketcherScreen *sketcherScreen = new SketcherScreen(this);
    setCentralWidget(sketcherScreen);
}