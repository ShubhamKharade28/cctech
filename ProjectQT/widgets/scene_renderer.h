#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>

#include <QMatrix4x4>

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
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Scene* scene;
    
    void drawAxis();

    QMatrix4x4 projection;
    QPoint lastMousePosition; 

    float cameraDistance; // distance from origin
    float cameraAzimuth; // camera angle around y-plane
    float cameraElevation; // camera angle in z-axis
};