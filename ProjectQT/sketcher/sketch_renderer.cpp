#include "sketch_renderer.h"
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>

SketchRenderer::SketchRenderer(QWidget* parent, Sketcher* sketch) : QOpenGLWidget(parent), sketch(sketch) {
    // Set main layout
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    setLayout(layout);
    
    interactionModeSelector = new QComboBox(this);
    interactionModeSelector->addItem("View Transform");
    interactionModeSelector->addItem("Edit");
    interactionModeSelector->setFixedSize(150, 30);

    connect(interactionModeSelector, &QComboBox::currentIndexChanged, this, [this](int index) {
        if(index == 0) {
            setInteractionMode(InteractionMode::ViewTransform);
        } else {
            setInteractionMode(InteractionMode::Edit);
        }
    });

    renderModeSelector = new QComboBox(this);
    renderModeSelector->addItem("Vertices Only");
    renderModeSelector->addItem("Wireframes");
    renderModeSelector->addItem("Shaded");
    renderModeSelector->addItem("Composite");
    renderModeSelector->setFixedSize(150, 30);

    connect(renderModeSelector, &QComboBox::currentIndexChanged, this, [this] (int index) {
        switch(index) {
            case 0: 
                setRenderMode(RenderMode::VerticesOnly);
                break;
            case 1:
                setRenderMode(RenderMode::Wireframe);
                break;
            case 2:
                setRenderMode(RenderMode::Shaded);
                break;
            case 3:
                setRenderMode(RenderMode::Composite);
                break;
            default:
                setRenderMode(RenderMode::Composite);
        }
        update();
    });


    auto* resetViewButton = new QPushButton("Reset View", this);
    resetViewButton->setFixedSize(150, 30);
    connect(resetViewButton, &QPushButton::clicked, this, resetView);

    auto* clearSketchButton = new QPushButton("Clear", this);
    clearSketchButton->setFixedSize(150, 30);
    connect(clearSketchButton, &QPushButton::clicked, this, clearSketch);
    

    // Add top layout
    auto* topLayout = new QHBoxLayout(this);
    topLayout->addWidget(interactionModeSelector);
    topLayout->addWidget(renderModeSelector);
    topLayout->addWidget(resetViewButton);
    topLayout->addWidget(clearSketchButton);
    topLayout->addStretch();

    layout->addLayout(topLayout);
    layout->addStretch();
}

SketchRenderer::~SketchRenderer() {
    delete sketch;
}

void SketchRenderer::setRenderMode(RenderMode mode = Wireframe) {
    this->renderMode = mode;
}

void SketchRenderer::setInteractionMode(InteractionMode mode = InteractionMode::ViewTransform) {
    this->interactionMode = mode;
}

void SketchRenderer::initializeGL() {
    initializeOpenGLFunctions(); // Initialize OpenGL functions
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Set the background color
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe mode for debugging
}

void SketchRenderer::resizeGL(int w, int h) {
    // Set the viewport to the new window size
    glViewport(0, 0, w, h);
    projection.setToIdentity();
    projection.perspective(45.0f, float(w)/h, 0.1f, 1000.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.constData());
    glMatrixMode(GL_MODELVIEW);

    drawAxis();
}

void SketchRenderer::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); 

    // model view transformation
    QMatrix4x4 modelView = getViewMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(modelView.constData());

    drawAxis(); 

    switch(renderMode) {
        case RenderMode::VerticesOnly:
            renderVertices();
            break;
        case RenderMode::Wireframe:
            renderVertices();
            renderEdges();
            break;
        case RenderMode::Shaded: {
            renderEdges();
            renderFaces();
            break;
        }
        case RenderMode::Solid: {
            renderSolids();
            break;
        }
        case RenderMode::Composite: {
            renderVertices();
            renderEdges();
            renderFaces();
            renderSolids();
        }
        default: {
            qDebug() << "Wrong rendering mode";
        }
    }
}

void SketchRenderer::clearSketch() {
    sketch->clear();
    update();
}

void SketchRenderer::resetView() {
    zoomFactor = 1;
    posX = 0;
    posY = 0;
    rotationX = 0.0f;
    rotationY = 0.0f;
    update();
}

QMatrix4x4 SketchRenderer::getViewMatrix(){
    QMatrix4x4 modelView;
    modelView.setToIdentity();

    // apply zoomm
    modelView.translate(posX, posY, -10*zoomFactor);

    // apply rotation (translate to center, rotate, then translate back to it's original position)
    modelView.translate(sceneCenter);
    modelView.rotate(rotationX, 1.0, 0.0f, 0.0f);
    modelView.rotate(rotationY, 0.0f, 1.0f, 0.0f);
    modelView.translate(-sceneCenter);

    // apply translation
    modelView.translate(posX, posY, 0);

    //  Rotate the world: Make Z axis vertical (instead of Y)
    // modelView.rotate(-90, 1.0f, 0.0f, 0.0f);

    return modelView;
}

void SketchRenderer::renderVertices() {
    glColor3f(1.0f, 0.0f, 0.0f); // Set color for vertices (red)
    glPointSize(5.0f); // Set point size for vertices

    glBegin(GL_POINTS);
    for (auto& vertex : sketch->getVertices()) {
        glVertex3f(vertex->getX(), vertex->getY(), vertex->getZ());
    }
    glEnd();
}

void SketchRenderer::renderEdges() {
    glColor3f(0.0f, 1.0f, 0.0f); // Set color for edges (green)
    glLineWidth(0.5f); // Set line width for edges
    glBegin(GL_LINES);
    for (auto& edge : sketch->getEdges()) {
        auto startVertex = edge->getStart();
        auto endVertex = edge->getEnd();
        glVertex3f(startVertex->getX(), startVertex->getY(), startVertex->getZ());
        glVertex3f(endVertex->getX(), endVertex->getY(), endVertex->getZ());
    }
    glEnd();
}

void SketchRenderer::renderFaces() {
    glColor3f(0.0f, 0.0f, 1.0f); // Set color for faces (blue)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for(auto& face : sketch->getFaces()) {
        glBegin(GL_POLYGON);
        auto vertices = face->getVertices();
        for (auto& vertex : vertices) {
            glVertex3f(vertex->getX(), vertex->getY(), vertex->getZ());
        }
        glEnd();
    }
}

void SketchRenderer::renderSolids() {
    glColor3f(1.0f, 1.0f, 0.0f); // Set color for solids (yellow)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(1.0f, 1.0f, 0.0f);
    
    auto solids = sketch->getSolids();
    for(auto& solid : solids){
        auto faces = solid->getFaces();
        for(auto& face : faces) {
            auto vertices = face->getVertices();
            glBegin(GL_POLYGON);
            for (auto& vertex : vertices) {
                glVertex3f(vertex->getX(), vertex->getY(), vertex->getZ());
            }
            glEnd();
        }
    }
}

void SketchRenderer::drawAxis() {
    double start = -100, end = 100;

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
    glLineWidth(0.1f); // Set line width
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

QPointF SketchRenderer::screenToWorld(QPointF screenPos) {
    float ndcX = (2.0f * screenPos.x()) / width() - 1.0f;
    float ndcY = 1.0f - (2.0f * screenPos.y()) / height();

    float xCoef = 6.2, yCoef = 4;

    float worldX = xCoef*(ndcX / zoomFactor);
    float worldY = yCoef*(ndcY / zoomFactor);
    QPointF mousePos = QPointF(worldX, worldY);
    return mousePos;
}

void SketchRenderer::setSelectedVertexIdx(int idx = -1) {
    selectedVertexIdx = idx;
}

void SketchRenderer::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        currentButton = "left";
    } else if(event->button() == Qt::RightButton) {
        currentButton = "right";
    }

    if (interactionMode == InteractionMode::Edit) {
        QPointF screenPos = event->pos();
        QPointF mousePos = screenToWorld(screenPos);

        double x = (double) mousePos.x();
        double y = (double) mousePos.y();
        double z = 0.0; 

        if(currentButton == "right") {
            sketch->addVertex(x, y, z);
            qDebug() << "Vertex added at " << x << y << z;
        } else if (currentButton == "left") {
            int vertexIdx = sketch->findVertex(x, y, z);
            setSelectedVertexIdx(vertexIdx);
            qDebug() << "Selected Vertex: " << vertexIdx;
        }
        update();
    }
    lastMousePosition = event->pos();
}

void SketchRenderer::mouseMoveEvent(QMouseEvent* event) {
    QPoint delta = event->pos() - lastMousePosition;

    if(interactionMode == InteractionMode::Edit && currentButton == "left") {
        if(selectedVertexIdx != -1) {
            QPointF screenPos = event->pos();
            QPointF mousePos = screenToWorld(screenPos);
            // QPointF deltaF = delta.toPointF();
            // deltaF = screenToWorld(deltaF);
            // QPointF newPos = mousePos + deltaF;

            // double x = newPos.x(), y = newPos.y(), z = 0;
            double x = mousePos.x(), y = mousePos.y(), z = 0;
            bool vertexMoved = sketch->moveVertex(selectedVertexIdx, x, y, z);
        }
    }
    else if (interactionMode == InteractionMode::ViewTransform) {
        
        if(currentButton == "left") {
            qDebug() << "Left button pressed";
            posX += delta.x() * sensitivity;
            posY -= delta.y() * sensitivity;
        } else if (currentButton == "right") {
            qDebug() << "Right button pressed";
            rotationX += delta.y();
            rotationY += delta.x();
        }
    }

    lastMousePosition = event->pos();
    update();
}

// zoom done
void SketchRenderer::wheelEvent(QWheelEvent* event) {
    if(event->angleDelta().y() > 0) {
        zoomFactor *= 1.1f;
    } else {
        zoomFactor /= 1.1f;
    }

    zoomFactor = std::clamp(zoomFactor, 0.01f, 50.0f);
    update();
}

void SketchRenderer::mouseReleaseEvent(QMouseEvent* event) {
    selectedVertexIdx = -1;
}