#include "scene_renderer.h"

#include "scene.h"
#include "drawable-shape.h"
#include "point.h"

#include <QOpenGLFunctions>
#include <QVBoxLayout>


SceneRenderer::SceneRenderer(QWidget* parent=nullptr, Scene* scene=nullptr)
    : QOpenGLWidget(parent), scene(scene) {
}

void SceneRenderer::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // dark blue background
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); 

    drawAxis();
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
    glLoadIdentity(); // resets matrix to default

    // camera settings
    
    glTranslatef(0, 0, -10);

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

    drawAxis();
}


void SceneRenderer::mousePressEvent(QMouseEvent* event) {
    
}

void SceneRenderer::mouseMoveEvent(QMouseEvent* event) {
    
    update();
}

void SceneRenderer::wheelEvent(QWheelEvent* event) {
    

    update();
}

void SceneRenderer::mouseReleaseEvent(QMouseEvent* event) {
    
}

class Color {
    public:
    float r,g,b;
    Color(float r, float g, float b): r(r), g(g), b(b) {};
};

void SceneRenderer::drawAxis() {
    // draw axis using 3 lines
    double start = -10, end = 10;
    vector<pair<Point3d, Point3d>> lines = {
        {Point3d(start, 0, 0), Point3d(end, 0, 0)}, 
        {Point3d(0, start, 0), Point3d(0, end, 0)},
        {Point3d(0, 0, start), Point3d(0, 0, end)}
    };

    vector<Color> colors = {
        Color(0, 1, 0), // green
        Color(1, 0.5, 0), // yellow
        Color(1, 0, 1)
    };

    glBegin(GL_LINES);
    for(int i=0; i<3; i++){
        Color color = colors[i];
        glColor3f(color.r, color.g, color.b);

        auto line = lines[i];
        auto p1 = line.first, p2 = line.second;
        
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    }
    glEnd();
}