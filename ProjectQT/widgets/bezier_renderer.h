#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>

#include "bezier_curve.h"

class BezierRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
 
public:
    explicit BezierRenderer(QWidget *parent = nullptr, BezierCurve *curve = nullptr);
 
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    BezierCurve* curve;
    
    void drawCurve();
    void drawControlPoints();

    int selectedPointIndex = -1;

private slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override; 

};