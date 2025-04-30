#pragma once 

#include "sketcher.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QMouseEvent>

class SketchRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
    Sketcher* sketch;
public: 
    SketchRenderer(QWidget* parent = nullptr, Sketcher* sketch = nullptr);   
    ~SketchRenderer();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private slots:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    // void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void renderVertices();
    void renderEdges();
    void renderFaces();
    void renderSolids();

    QMatrix4x4 getViewMatrix();
    void drawAxis();

    QMatrix4x4 projection;
    QPoint lastMousePosition; 
    string currentButton = "left";

    float zoomFactor = 1.0f;
    float posX = 0, posY = 0;
    float sensitivity = 0.1;

    QVector3D sceneCenter = {0,0,0};
    float rotationX = 0.0f;
    float rotationY = 0.0f; 
};