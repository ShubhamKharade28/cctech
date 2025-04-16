#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>

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
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Scene* scene;
    bool isDragging;
    QPoint lastMousePos;
    float zoomFactor;
    float rotationX, rotationY, rotationZ;
};