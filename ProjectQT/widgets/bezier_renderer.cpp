#include "bezier_renderer.h"

#include <QDebug>
#include <QOpenGLFunctions>
#include <QPOintF>

BezierRenderer::BezierRenderer(QWidget *parent, BezierCurve* curve)
: QOpenGLWidget(parent), curve(curve) {
    qDebug() << "BezierRenderer created";
}

void BezierRenderer::initializeGL()
{
    qDebug() << "BezierRenderer initialized";
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void BezierRenderer::resizeGL(int w, int h) {
    qDebug() << "BezierRenderer resized to" << w << "x" << h;
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

void BezierRenderer::paintGL() {
    qDebug() << "paintGL called";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawCurve();
    drawControlPoints();
}

// use curve->getCurvePoints(), and draw those points using openGL
void BezierRenderer::drawCurve() {
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

void BezierRenderer::drawControlPoints() {
    vector<Point> controlPoints = curve->getControlPoints();
    glPointSize(10.0f); // Set point size
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    for (const auto& point : controlPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void BezierRenderer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPointF pos = event->pos();
        float x = (2.0f * pos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * pos.y() / height());
        selectedPointIndex = curve->findControlPoint(x, y, 0.1); // 0.1f is the influence radius
        update();
    } else if(event->button() == Qt::RightButton) {
        QPointF pos = event->pos();
        float x = (2.0f * pos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * pos.y() / height());
        curve->addControlPoint(x,y);
        update();
    }
}

void BezierRenderer::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPointF pos = event->pos();
        float x = (2.0f * pos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * pos.y() / height());
        curve->moveControlPoint(selectedPointIndex, x, y);
        update();
    }
}