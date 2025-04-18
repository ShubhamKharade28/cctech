#include "scene_renderer.h"

#include "scene.h"
#include "drawable-shape.h"

#include <QOpenGLFunctions>
#include <QVBoxLayout>


SceneRenderer::SceneRenderer(QWidget* parent=nullptr, Scene* scene=nullptr)
    : QOpenGLWidget(parent), scene(scene),
    isDragging(false), zoomFactor(1.0f), rotationX(0.0f), rotationY(0.0f) {
}

void SceneRenderer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // dark blue background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // Enable back-face culling
}

void SceneRenderer::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = GLfloat(w) / h;
    GLfloat fovy = 50.0f;
    GLfloat near = 0.1f;
    GLfloat far = 500.0f;
    GLfloat top = tan(fovy * M_PI / 360.0f) * near;
    GLfloat bottom = -top;
    GLfloat right = top * aspect;
    GLfloat left = -right;

    glFrustum(left, right, bottom, top, near, far);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SceneRenderer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply scaling (zoom)
    // glScalef(zoomFactor, zoomFactor, zoomFactor);

    // Apply rotation
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f); // Rotate along the X-axis
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f); // Rotate along the Y-axis
    // glRotatef(rotationZ, 0.0f, 0.0f, 1.0f); 

    // Move camera back
    // glTranslatef(0, 0, -10 + zoomFactor);
    glTranslatef(0, 0, -10 + zoomFactor); // Move camera back

    for (auto& drawable : scene->getDrawableShapes()) {
        auto triangles = drawable.getTriangles();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set wireframe mode

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

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Reset to normal fill mode
    }
}

void SceneRenderer::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->pos(); // Capture the current position for rotation
    }
}

void SceneRenderer::mouseMoveEvent(QMouseEvent* event) {
    if (isDragging) {
        int dx = event->x() - lastMousePos.x();
        int dy = event->y() - lastMousePos.y();

        if (event->buttons() & Qt::LeftButton) {
            // Rotate X and Y
            rotationX -= dy * 0.5f;
            rotationY -= dx * 0.5f;
        } else if (event->buttons() & Qt::RightButton) {
            // Rotate Z
            rotationZ -= dx * 0.5f;
        }

        lastMousePos = event->pos();
        update();
    }
}

void SceneRenderer::wheelEvent(QWheelEvent* event) {
    // int delta = event->angleDelta().y();

    // if (delta > 0) {
    //     zoomFactor *= 1.1f; // Zoom in
    // } else {
    //     zoomFactor /= 1.1f; // Zoom out
    // }
    zoomFactor += event->angleDelta().y() / 600.0f;

    update(); // Request OpenGL widget to re-render
}

void SceneRenderer::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
}

