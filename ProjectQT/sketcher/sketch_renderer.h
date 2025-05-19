#pragma once 

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QMutex>
#include <QComboBox>
#include <QVBoxLayout>


#include "sketcher.h"
#include "file-utils.h"

enum RenderMode {
    VerticesOnly,
    Wireframe,
    Shaded,
    Solid,
    Composite
};

enum InteractionMode {
    ViewTransform,
    Edit
};

enum EditMode {
    Vertice,
    Edge, 
    Face
};

class SketchRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
    Sketcher* sketch;
public: 
    SketchRenderer(QWidget* parent = nullptr, Sketcher* sketch = nullptr);   
    ~SketchRenderer();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private slots:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void setRenderMode(RenderMode mode);
    void setInteractionMode(InteractionMode mode);
    void setSelectedVertexIdx(int index);

public slots:
    void resetView();
    void clearSketch();

private:
    void renderVertices();
    void renderEdges();
    void renderFaces();
    void renderSolids();
    // void renderBoundingBox();
    
    RenderMode renderMode = RenderMode::VerticesOnly;
    InteractionMode interactionMode = InteractionMode::ViewTransform;
    EditMode editMode = EditMode::Vertice;

    int selectedVertexIdx = -1;

    QComboBox* interactionModeSelector;
    QComboBox* renderModeSelector;
    QVBoxLayout* layout;

    QMatrix4x4 getViewMatrix();
    void drawAxis();
    QPointF screenToWorld(QPointF screenPos);

    QMatrix4x4 projection;
    QPoint lastMousePosition; 
    string currentButton = "left";

    float zoomFactor = 1.0f;
    float posX = 0, posY = 0;
    float sensitivity = 0.1;

    QVector3D sceneCenter = {0,0,0};
    float rotationX = 0.0f;
    float rotationY = 0.0f; 

    // STL files
    vector<StlShape> stlShapes;

private slots:
    void importSTLFile();
    void renderSTLShapes();
    void renderSTLIntersections();

signals: 
    void sketchUpdated();
};