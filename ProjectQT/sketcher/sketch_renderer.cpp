#include "sketch_renderer.h"

SketchRenderer::SketchRenderer(QWidget* parent, Sketcher* sketch) : QOpenGLWidget(parent), sketch(sketch) {
    // Initialize OpenGL functions
    initializeOpenGLFunctions(); // Initialize OpenGL functions
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Set the background color
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe mode for debugging
}

SketchRenderer::~SketchRenderer() {
    delete sketch;// Cleanup if needed
}

void SketchRenderer::initializeGL() {
    // Set up OpenGL state
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white

}

void SketchRenderer::resizeGL(int w, int h) {
    // Set the viewport to the new window size
    glViewport(0, 0, w, h);
}

void SketchRenderer::paintGL() {
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Call your rendering methods here
    renderVertices();
    renderEdges();
    renderFaces();
    renderSolids();
}