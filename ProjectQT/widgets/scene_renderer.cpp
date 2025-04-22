#include "scene_renderer.h"

#include "scene.h"
#include "drawable-shape.h"
#include "point.h"

#include <QOpenGLFunctions>
#include <QVBoxLayout>

#include <QDebug>

#include <bits/stdc++.h>
using namespace std;


SceneRenderer::SceneRenderer(QWidget* parent=nullptr, Scene* scene=nullptr)
    : QOpenGLWidget(parent), 
    scene(scene), posX(0), posY(0), sensitivity(0.01f)
{
    // other initializations
}

void SceneRenderer::initializeGL() {
    initializeOpenGLFunctions(); // Initialize OpenGL functions
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Set the background color
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe mode for debugging

    /* lightinng code
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
 
    GLfloat lightAmbient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, -10.0f, 10.0f, 1.0f };
 
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
 
    GLfloat matSpecular[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess[] = { 5.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, lightAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, lightDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
 
    glEnable(GL_NORMALIZE);
    */

}

void SceneRenderer::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    projection.setToIdentity();

    /*  fov - field of view in degrees
        aspect ratio - width / height 
        near clipping plane - closest distance where objects are rendered
        far clipping plane - furthest distance where objects are still visible  
    */ 
    projection.perspective(45.0f, float(w)/h, 0.1f, 1000.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.constData());
    glMatrixMode(GL_MODELVIEW);
    drawAxis();
}

void SceneRenderer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // resets matrix to default

    // model view transformation
    QMatrix4x4 modelView;
    modelView.setToIdentity();

    // apply zoomm
    modelView.translate(posX, posY, -5.0*zoomFactor);

    // apply rotation (translate to center, rotate, then translate back to it's original position)
    modelView.translate(sceneCenter);
    modelView.rotate(rotationX, 1.0, 0.0f, 0.0f);
    modelView.rotate(rotationY, 0.0f, 1.0f, 0.0f);
    modelView.translate(-sceneCenter);

    // apply translation
    modelView.translate(posX, posY, 0);

    // TODO: other transformations later to be done
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(modelView.constData());

    drawAxis();
    drawShapes();
}

void SceneRenderer::drawShapes() {
    glColor3f(0.0f, 1.0f, 0.5f);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Set fill mode
    for (auto& drawable : scene->getDrawableShapes()) {
        auto triangles = drawable.getTriangles();

        glBegin(GL_TRIANGLES);
        for (const auto& tri : triangles) {
            Vector v1 = tri.vertex1;
            Vector v2 = tri.vertex2;
            Vector v3 = tri.vertex3;
            glVertex3f(v1[0], v1[1], v1[2]);
            glVertex3f(v2[0], v2[1], v2[2]);
            glVertex3f(v3[0], v3[1], v3[2]);
        }
        glEnd();
    }

    // Draw edges of the triangles
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set wireframe mode
    glColor3f(1.0f, 0.5f, 0.0f); // Set color for the edges (red)

    for (auto& drawable : scene->getDrawableShapes()) {
        auto triangles = drawable.getTriangles();

        glBegin(GL_LINES);
        for (const auto& tri : triangles) {
            Vector v1 = tri.vertex1;
            Vector v2 = tri.vertex2;
            Vector v3 = tri.vertex3;

            // Draw edges
            glVertex3f(v1[0], v1[1], v1[2]);
            glVertex3f(v2[0], v2[1], v2[2]);

            glVertex3f(v2[0], v2[1], v2[2]);
            glVertex3f(v3[0], v3[1], v3[2]);

            glVertex3f(v3[0], v3[1], v3[2]);
            glVertex3f(v1[0], v1[1], v1[2]);
        }
        glEnd();
    }
}

void SceneRenderer::drawAxis() {
    double start = -20, end = 20;

    // Define 3 axis lines (X, Y, Z)
    QVector<QPair<QVector3D, QVector3D>> lines = {
        {QVector3D(start, 0, 0), QVector3D(end, 0, 0)},  // X-axis
        {QVector3D(0, start, 0), QVector3D(0, end, 0)},  // Y-axis
        {QVector3D(0, 0, start-20), QVector3D(0, 0, end+20)}   // Z-axis
    };

    // Define colors for each axis
    QVector<QVector3D> colors = {
        QVector3D(0.0f, 1.0f, 0.0f),   // green for X
        QVector3D(1.0f, 0.5f, 0.0f),   // orange/yellow for Y
        QVector3D(1.0f, 1.0f, 1.0f)    // white for Z
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(2.0f); // Set line width
    glBegin(GL_LINES);
    for (int i = 0; i < 3; ++i) {
        QVector3D color = colors[i];
        glColor3f(color.x(), color.y(), color.z());

        QVector3D p1 = lines[i].first;
        QVector3D p2 = lines[i].second;

        glVertex3f(p1.x(), p1.y(), p1.z());
        glVertex3f(p2.x(), p2.y(), p2.z());
    }
    glEnd();
}


void SceneRenderer::mousePressEvent(QMouseEvent* event) {
    lastMousePosition = event->pos();
    if(event->button() == Qt::LeftButton) {
        currentButton = "left";
    } else if(event->button() == Qt::RightButton) {
        currentButton = "right";
    }
}

void SceneRenderer::mouseMoveEvent(QMouseEvent* event) {
    QPoint delta = event->pos() - lastMousePosition;

    if(currentButton == "left") {
        qDebug() << "Left button pressed";
        posX += delta.x() * sensitivity;
        posY -= delta.y() * sensitivity;
    } else if (currentButton == "right") {
        qDebug() << "Right button pressed";
        rotationX += delta.y();
        rotationY -= delta.x();
    }

    lastMousePosition = event->pos();
    update();
}

// zoom done
void SceneRenderer::wheelEvent(QWheelEvent* event) {
    if(event->angleDelta().y() > 0) {
        zoomFactor *= 1.1f;
    } else {
        zoomFactor /= 1.1f;
    }

    zoomFactor = std::clamp(zoomFactor, 0.1f, 10.0f);
    update();
}