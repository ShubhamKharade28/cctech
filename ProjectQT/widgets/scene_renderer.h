#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Scene;

class SceneRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    SceneRenderer(QWidget* parent, Scene* scene);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    Scene* scene;
};