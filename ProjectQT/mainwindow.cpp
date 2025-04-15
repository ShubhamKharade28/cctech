#include "mainwindow.h"

#include <QWidget>

#include "screens/scenecreator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->resize(1000, 700);
    setWindowTitle("Project 3D");

    SceneCreator *sceneCreator = new SceneCreator(this);
    setCentralWidget(sceneCreator);
}

MainWindow::~MainWindow() {}
