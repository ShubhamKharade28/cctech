#include "screen_selector_dialog.h"

ScreenSelectorDialog::ScreenSelectorDialog(QWidget *parent)
    : QDialog(parent), selectedScreen(-1) {

    auto* layout = new QVBoxLayout(this);

    auto* sceneButton = new QPushButton("Draw 3D Scene", this);
    auto* bezierButton = new QPushButton("Draw Bezier Curve", this);
    auto* sketcherButton = new QPushButton("Draw Sketch", this);

    connect(sceneButton, &QPushButton::clicked, this, &ScreenSelectorDialog::selectSceneCreator);
    connect(bezierButton, &QPushButton::clicked, this, &ScreenSelectorDialog::selectBezierSketcher);
    connect(sketcherButton, &QPushButton::clicked, this, &ScreenSelectorDialog::selectSketcher);

    layout->addWidget(sceneButton);
    layout->addWidget(bezierButton);
    layout->addWidget(sketcherButton);

    setLayout(layout);
    setWindowTitle("What do want to do?");
}

int ScreenSelectorDialog::getSelectedScreen() {
    return selectedScreen;
}

void ScreenSelectorDialog::selectSceneCreator() {
    selectedScreen = 0;
    accept();
}

void ScreenSelectorDialog::selectBezierSketcher() {
    selectedScreen = 1;
    accept();
}

void ScreenSelectorDialog::selectSketcher() {
    selectedScreen = 2;
    accept();
}