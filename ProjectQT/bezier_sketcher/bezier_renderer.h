#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QComboBox>
#include <QVBoxLayout>

#include "bezier_curve.h"

class BezierRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
 
public:
    explicit BezierRenderer(QWidget *parent = nullptr, BezierCurve *curve1 = nullptr, BezierCurve *curve2 = nullptr);
 
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    BezierCurve* curve1;
    BezierCurve* curve2;
    
    void drawCurve();
    void drawControlPoints();
    void drawIntersections();

    int selectedPointIndex = -1;
    BezierCurve* currentCurve;
    QComboBox* bezierSelector;

private slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override; 

    void selectBezier(int index);

};