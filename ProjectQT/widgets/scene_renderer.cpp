#include "scene_renderer.h"

#include <QLabel>
#include <QVBoxLayout>

#include "scene.h"
#include "drawable-shape.h"

#include <QOpenGLFunctions>

SceneRenderer::SceneRenderer(QWidget* parent=nullptr, Scene* scene=nullptr)
    : QOpenGLWidget(parent), scene(scene) {
}

void SceneRenderer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // dark blue background
    glEnable(GL_DEPTH_TEST);
}

void SceneRenderer::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
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

void SceneRenderer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, 0, -10); // move camera back

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
}
