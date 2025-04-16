#pragma once

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

#include "point.h"
#include "bezier_curve.h"

#include <bits/stdc++.h>
using namespace std;

class Sidebar: public QWidget {
Q_OBJECT
public:
    explicit Sidebar(QWidget* parent = nullptr, BezierCurve* curve = nullptr);

private:
    QFormLayout* inputForm;
    QLineEdit* xField;
    QLineEdit* yField;
    QPushButton* addPointButton;

    BezierCurve* curve;
    
private slots:
    void onAddPointButtonClicked();
};