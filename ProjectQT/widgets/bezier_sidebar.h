#pragma once

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

#include "point.h"
#include "bezier_curve.h"
#include "bezier_renderer.h"

#include <bits/stdc++.h>
using namespace std;

class BezierSidebar: public QWidget {
Q_OBJECT
public:
    explicit BezierSidebar(QWidget* parent = nullptr, BezierCurve* curve = nullptr, BezierRenderer* renderer = nullptr);

private:
    BezierCurve* curve;
    BezierRenderer* renderer;
    QFormLayout* inputForm;
    QLineEdit* xField;
    QLineEdit* yField;
    QPushButton* addPointButton;
    QListWidget* pointListWidget;
    QListWidgetItem* selectedItem = nullptr;
    QPushButton* deletePointButton;
    QPushButton* clearPointsButton;

    void addControlPoint(Point p);
    void modifyControlPoint(int index, Point p);
    void removeControlPoint(int index);
    void clearControlPoints();
    void setResolution(int resolution);
    void updateCurvePoints();
    
private slots:
    void onAddPointButtonClicked();
    void onDeletePointButtonClicked();
    void onClearPointsButtonClicked();
    // void onPointListItemClicked(QListWidgetItem* item);
};