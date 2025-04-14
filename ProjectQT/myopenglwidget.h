#pragma once
 
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
 
class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
 
public:
    MyOpenGLWidget(QWidget *parent = nullptr);
    ~MyOpenGLWidget();
 
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    private slots:
    void updateRotation(); // Slot to update rotation angle

private:
    float angleX;
    float angleY;
    QTimer timer;

    void paint2D();
    void paint3D();
};