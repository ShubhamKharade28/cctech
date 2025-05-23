#include "bezier_sketcher.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>

BezierSketcher::BezierSketcher(QWidget *parent) : QWidget(parent) {
    auto* layout = new QHBoxLayout(this);

    const int numOfPoints = 40;
    curve1 = new BezierCurve(numOfPoints);
    curve2 = new BezierCurve(numOfPoints);

    renderer = new BezierRenderer(this, curve1, curve2);
    sidebar = new BezierSidebar(this, curve1, renderer);

    // Add all widgets to layout
    layout->addWidget(sidebar, 3);
    layout->addWidget(renderer, 7);

    setLayout(layout);
}

BezierSketcher::~BezierSketcher() {}