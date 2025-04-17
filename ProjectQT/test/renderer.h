#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "bezier_curve.h"

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
 
public:
    explicit Renderer(QWidget *parent = nullptr, BezierCurve *curve = nullptr);
 
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void drawCurve();
    void drawControlPoints();

private:
    BezierCurve* curve;
};