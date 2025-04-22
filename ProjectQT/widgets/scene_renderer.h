#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>

#include <QMatrix4x4>
#include <QPoint> 

#include <bits/stdc++.h>
using namespace std;

class Scene;

class SceneRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    SceneRenderer(QWidget* parent, Scene* scene);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    // Mouse events

private slots:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    // void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Scene* scene;
    
    void drawAxis();
    void drawShapes();

    bool initialised = false;

    QMatrix4x4 projection;
    QPoint lastMousePosition; 

    float zoomFactor;
    float posX, posY;
    float sensitivity;

    QVector3D sceneCenter = {0,0,0};
    float rotationX = 0.0f;
    float rotationY = 0.0f;

    string currentButton = "left";

    // float cameraDistance; // distance from origin
    // float cameraAzimuth; // camera angle around y-plane
    // float cameraElevation; // camera angle in z-axis
};