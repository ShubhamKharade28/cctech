#include "renderer.h"

Renderer::Renderer()(QWidget *parent, BezierCurve* curve)
: QOpenGLWidget(parent), curve(curve) {

}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();
    glColor3f(0, 0, 0);
}

void Renderer::paintGL() {
    
}

void Renderer::resizeGL(int w, int h) {

}