#include "sidebar.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include <bits/stdc++.h>
using namespace std;

Sidebar::Sidebar(QWidget* parent, BezierCurve* curve, Renderer* renderer): QWidget(parent), curve(curve), renderer(renderer) {
    auto* layout = new QVBoxLayout(this);

    auto* label1 = new QLabel("Add Control Points", this);

    // Input form and it's fields
    inputForm = new QFormLayout(this);
    xField = new QLineEdit(this);
    yField = new QLineEdit(this);

    inputForm->addRow("x: ", xField);
    inputForm->addRow("y: ", yField);

    // Button to add control points
    addPointButton = new QPushButton("Add Point");
    connect(addPointButton, &QPushButton::clicked, 
        this, &Sidebar::onAddPointButtonClicked);

    auto* label2 = new QLabel("Control Points", this);

    pointListWidget = new QListWidget(this);
    // pointListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // pointListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // pointListWidget->setAlternatingRowColors(true);
    // pointListWidget->setSortingEnabled(true);
    // pointListWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    // delete point button
    deletePointButton = new QPushButton("Delete Point", this);
    connect(deletePointButton, &QPushButton::clicked, 
        this, &Sidebar::onDeletePointButtonClicked);

    // clear points button 
    clearPointsButton = new QPushButton("Clear Points", this);
    connect(clearPointsButton, &QPushButton::clicked, 
        this, &Sidebar::onClearPointsButtonClicked);
    
    // Add inputForm and addPointButton to sidebar
    layout->addWidget(label1);
    layout->addLayout(inputForm);
    layout->addWidget(addPointButton);
    layout->addWidget(label2);
    layout->addWidget(pointListWidget);
    layout->addWidget(deletePointButton);
    layout->addWidget(clearPointsButton);
    
    setLayout(layout);
}

void Sidebar::onAddPointButtonClicked() {
    bool xOk, yOk;
    double x = xField->text().toDouble(&xOk);
    double y = yField->text().toDouble(&yOk);

    Point p(x, y);
    if (xOk && yOk) {
        addControlPoint(p);

        QListWidgetItem* item = new QListWidgetItem(QString("(%1, %2)").arg(x).arg(y));
        pointListWidget->addItem(item);

        xField->clear();
        yField->clear();
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid numbers for x and y.");
    }
}

void Sidebar::onDeletePointButtonClicked() {
    QListWidgetItem* item = pointListWidget->currentItem();

    if (item) {
        int index = pointListWidget->row(item);
        removeControlPoint(index);
        delete item;
    } else {
        QMessageBox::warning(this, "No Selection", "Please select a control point to delete.");
    }
}

void Sidebar::onClearPointsButtonClicked() {
    clearControlPoints();
    pointListWidget->clear();
}

void Sidebar::addControlPoint(Point p) {
    curve->addControlPoint(p);
    renderer->update();
}

void Sidebar::modifyControlPoint(int index, Point p) {
    curve->modifyControlPoint(index, p.x, p.y);
    renderer->update();
}

void Sidebar::removeControlPoint(int index) {
    curve->removeControlPoint(index);
    renderer->update();
}

void Sidebar::clearControlPoints() {
    curve->clearControlPoints();
    renderer->update();
}

void Sidebar::setResolution(int resolution) {
    curve->setResolution(resolution);
    renderer->update();
}

void Sidebar::updateCurvePoints() {
    curve->getCurvePoints(true);
    renderer->update();
}