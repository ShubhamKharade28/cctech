#pragma once 

#include "sketcher.h"
#include "sketch_renderer.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>

class SketcherScreen : public QWidget {
    Q_OBJECT

    Sketcher* sketch;
    SketchRenderer* renderer;

    void setupUI();
    void setupSidebarUI(QVBoxLayout* sidebar);

public:
    explicit SketcherScreen(QWidget* parent = nullptr);
    ~SketcherScreen();

private:
    // lists for vertices, edges, faces, and solids
    QListWidget* vertexListWidget;
    QListWidget* edgeListWidget;
    QListWidget* faceListWidget;
    QListWidget* solidListWidget;

    // vertex inputs
    QLineEdit* vertexXInput;
    QLineEdit* vertexYInput;
    QLineEdit* vertexZInput;
    QPushButton* addVertexButton;

    // edge inputs
    QLineEdit* edgeStartInput;
    QLineEdit* edgeEndInput;
    QPushButton* addEdgeButton;

    // face inputs
    QLineEdit* faceEdgeInput;
    QPushButton* addFaceButton;

    // extrude face button
    QPushButton* extrudeFaceButton;
    QLineEdit* extrudeHeightInput;

    // revolve face button 
    QPushButton* revolveFaceButton;
    QLineEdit* revolveAngleInput;
    QLineEdit* revolveAxisInput; // axis of revolution will be an edge (future use)
    
    // selected face for extrusion (for revolve in future)
    int selectedFaceIndex = -1;

private slots:
    void addVertex();
    void addEdge();
    void addFace();
    void addSolid();

    void updateVertexList();
    void updateEdgeList();
    void updateFaceList();
    void updateSolidList();

    void selectFace(QListWidgetItem* item);
    void extrudeFace();
    void revolveFace();

signals:
    void vertexAdded();
    void edgeAdded();
    void faceAdded();
    void solidAdded();
};