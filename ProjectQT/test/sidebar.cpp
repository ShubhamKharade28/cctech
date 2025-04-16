#include "sidebar.h"

#include <QVBoxLayout>

#include <bits/stdc++.h>
using namespace std;

// Sidebar::Sidebar(QWidget* parent, vector<Point*> controlPoints): QWidget(parent), controlPoints(controlPoints) {
Sidebar::Sidebar(QWidget* parent, BezierCurve* curve): QWidget(parent), curve(curve) {
    auto* layout = new QVBoxLayout(this);

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
    
    // Add inputForm and addPointButton to sidebar
    layout->addLayout(inputForm);
    layout->addWidget(addPointButton);
}

void Sidebar::onAddPointButtonClicked() {
    
}