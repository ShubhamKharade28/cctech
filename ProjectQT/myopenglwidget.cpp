#include "myopenglwidget.h"
 
MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), angleX(0), angleY(0)
{
    timer.setInterval(16); // ~60 FPS
    connect(&timer, &QTimer::timeout, this, &MyOpenGLWidget::updateRotation);
    timer.start();
}

 
MyOpenGLWidget::~MyOpenGLWidget() {}
 
void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);            // Enable depth testing
    // glEnable(GL_CULL_FACE);             // Optional: remove hidden surfaces
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
}
 
void MyOpenGLWidget::resizeGL(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);             // Set the viewport

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = GLfloat(w) / h;
    GLfloat fovy = 100.0f;
    GLfloat near = 0.1f;
    GLfloat far = 100.0f;
    GLfloat top = tan(fovy * M_PI / 360.0f) * near;
    GLfloat bottom = -top;
    GLfloat right = top * aspect;
    GLfloat left = -right;

    glFrustum(left, right, bottom, top, near, far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyOpenGLWidget::updateRotation()
{
    angleX += 1.0f;
    angleY += 0.5f;
    update(); // Triggers repaint (calls paintGL)
}

void MyOpenGLWidget::paint2D() {
    glClear(GL_COLOR_BUFFER_BIT);
 
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex2f(0.0f,  0.5f);     // Top
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex2f(-0.5f, -0.5f);    // Left
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex2f(0.5f, -0.5f);     // Right
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex2f(0.3f,  0.5f);     // Top
    glColor3f(0.0f, 1.0f, 1.0f); // Greenish Blue
    glVertex2f(1.0f, -0.5f);     // Right
    glColor3f(2.0f, 0.0f, 1.0f); // Blue
    glVertex2f(0.5f, -0.5f);     // Right
    glEnd();
}

void MyOpenGLWidget::paint3D() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -2.5f);

    // Apply rotation
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis

    // Draw tetrahedron
    glBegin(GL_TRIANGLES);

    // Front face
    glColor3f(1, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);

    // Right face
    glColor3f(0, 1, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(1, -1, 1);
    glVertex3f(0, -1, -1);

    // Left face
    glColor3f(0, 0, 1);
    glVertex3f(0, 1, 0);
    glVertex3f(0, -1, -1);
    glVertex3f(-1, -1, 1);

    // Bottom face
    glColor3f(1, 1, 0);
    glVertex3f(-1, -1, 1);
    glVertex3f(0, -1, -1);
    glVertex3f(1, -1, 1);

    glEnd();
}
 
void MyOpenGLWidget::paintGL()
{
    paint3D();
}