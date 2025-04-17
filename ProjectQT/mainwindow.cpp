#include "mainwindow.h"

#include <QWidget>

// #include "screens/scenecreator.h"

#include "test-screen.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // this->resize(1000, 700);
    // setWindowTitle("Project 3D");

    // SceneCreator *sceneCreator = new SceneCreator(this);
    // setCentralWidget(sceneCreator);

    this->resize(1000, 700);
    setWindowTitle("Test - Bezier Curve");

    TestScreen* testScreen = new TestScreen(this);
    setCentralWidget(testScreen);
}

MainWindow::~MainWindow() {}
