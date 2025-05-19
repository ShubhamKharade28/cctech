#include "bezier_renderer.h"

#include <QDebug>
#include <QOpenGLFunctions>
#include <QPOintF>

void BezierRenderer::selectBezier(int index) {
    if(index == 0){
        currentCurve = curve1;
    } else {
        currentCurve = curve2;
    }
    update();
}

BezierRenderer::BezierRenderer(QWidget *parent, BezierCurve* curve1, BezierCurve* curve2)
: QOpenGLWidget(parent) {
    this->curve1 = curve1;
    this->curve2 = curve2;

    qDebug() << "BezierRenderer created";
    currentCurve = this->curve1;

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    setLayout(layout);
    
    bezierSelector = new QComboBox(this);
    bezierSelector->addItem("Curve 1");
    bezierSelector->addItem("Curve 2");
    bezierSelector->setFixedSize(150, 30);

    connect(bezierSelector, &QComboBox::currentIndexChanged, this, selectBezier);
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
    drawIntersections();
}

// use curve->getCurvePoints(), and draw those points using openGL
void BezierRenderer::drawCurve() {
    cout << "Drawing curve" << endl;
    vector<Point> curvePoints1 = curve1->getCurvePoints(true);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glLineWidth(2.0f); // Set line width

    for (const auto& point : curvePoints1) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    vector<Point> curvePoints2 = curve2->getCurvePoints(true);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glLineWidth(2.0f); // Set line width
    for (const auto& point : curvePoints2) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void BezierRenderer::drawControlPoints() {
    vector<Point> controlPoints1 = curve1->getControlPoints();
    glPointSize(5.0f); // Set point size
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    for (const auto& point : controlPoints1) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    vector<Point> controlPoints2 = curve2->getControlPoints();
    glPointSize(5.0f); // Set point size
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 1.0f); // Blue color
    for (const auto& point : controlPoints2) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void BezierRenderer::drawIntersections() {
    if(!curve1 || !curve2) return;

    vector<Point> intersections = curve1->findIntersectionWith(curve2);

    glPointSize(12.0f);               // Make intersection points visible
    glColor3f(0.5f, 1.0f, 1.0f);     // Red color for intersection points

    glBegin(GL_POINTS);
    for (Point& p : intersections) {
        glVertex2f(p.x, p.y);        // Plot point
    }
    glEnd();
}

void BezierRenderer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPointF pos = event->pos();
        float x = (2.0f * pos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * pos.y() / height());
        selectedPointIndex = currentCurve->findControlPoint(x, y, 0.1); // 0.1f is the influence radius
        update();
    } else if(event->button() == Qt::RightButton) {
        QPointF pos = event->pos();
        float x = (2.0f * pos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * pos.y() / height());
        currentCurve->addControlPoint(x,y);
        update();
    }
}

void BezierRenderer::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPointF pos = event->pos();
        float x = (2.0f * pos.x() / width()) - 1.0f;
        float y = 1.0f - (2.0f * pos.y() / height());
        currentCurve->moveControlPoint(selectedPointIndex, x, y);
        update();
    }
}