#include "test-window.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

TestWindow::TestWindow(QWidget *parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);

    int numOfPoints = 20;
    curve = new BezierCurve(numOfPoints);

    renderer = new Renderer(this, curve);
    sidebar = new Sidebar(this, curve);

    // Add all widgets to layout
    layout->addWidget(sidebar, 0.3);
    layout->addWidget(renderer, 0.7);
}

TestWindow::~TestWindow() {}