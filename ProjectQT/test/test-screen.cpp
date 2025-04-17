#include "test-screen.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

TestScreen::TestScreen(QWidget *parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);

    int numOfPoints = 20;
    curve = new BezierCurve(numOfPoints);

    renderer = new Renderer(this, curve);
    sidebar = new Sidebar(this, curve, renderer);

    // Add all widgets to layout
    layout->addWidget(sidebar, 3);
    layout->addWidget(renderer, 7);

    setLayout(layout);
}

TestScreen::~TestScreen() {}