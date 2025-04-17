#include "renderer.h"
#include <QDebug>
#include <QOpenGLFunctions>
#include <QPOintF>

Renderer::Renderer(QWidget *parent, BezierCurve* curve)
: QOpenGLWidget(parent), curve(curve) {
    qDebug() << "Renderer created";
}

void Renderer::initializeGL()
{
    qDebug() << "Renderer initialized";
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Renderer::resizeGL(int w, int h) {
    qDebug() << "Renderer resized to" << w << "x" << h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glTranslatef(0.0f, 0.0f, -1.0f); // Move the camera back

    // Set up orthographic projection for 2D rendering
    if (w > h) {
        float aspect = float(w) / float(h);
        glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    } else {
        float aspect = float(h) / float(w);
        glOrtho(-1.0, 1.0, -aspect, aspect, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

void Renderer::paintGL() {
    qDebug() << "paintGL called";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawCurve();
    drawControlPoints();
    
    // draw triangle to test
    // glBegin(GL_TRIANGLES);
    // glColor3f(1.0f, 0.0f, 0.0f); // Red color
    // glVertex2f(-0.5f, -0.5f); // Bottom left
    // glVertex2f(0.5f, -0.5f);  // Bottom right
    // glVertex2f(0.0f, 0.5f);   // Top
    // glEnd();
}

// use curve->getCurvePoints(), and draw those points using openGL
void Renderer::drawCurve() {
    cout << "Drawing curve" << endl;
    vector<Point> curvePoints = curve->getCurvePoints(true);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glLineWidth(2.0f); // Set line width
    for (const auto& point : curvePoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void Renderer::drawControlPoints() {
    vector<Point> controlPoints = curve->getControlPoints();
    glPointSize(10.0f); // Set point size
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    for (const auto& point : controlPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void Renderer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPointF pos = event->pos();
        float x = (2.0f * pos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * pos.y() / height());
        selectedPointIndex = curve->findControlPoint(x, y, 0.1); // 0.1f is the influence radius
        update();
    }
}

void Renderer::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPointF pos = event->pos();
        float x = (2.0f * pos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * pos.y() / height());
        curve->moveControlPoint(selectedPointIndex, x, y);
        update();
    }
}