
#include "sketcher.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class SketchRenderer : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
    Sketcher* sketch;
public: 
    SketchRenderer(QWidget* parent = nullptr, Sketcher* sketch = nullptr);   
    ~SketchRenderer();

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // Add your rendering methods here
    void renderVertices(){};
    void renderEdges(){};
    void renderFaces(){};
    void renderSolids(){};
};