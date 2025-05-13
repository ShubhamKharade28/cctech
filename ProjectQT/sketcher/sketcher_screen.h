#pragma once 

#include "sketcher.h"
#include "sketch_renderer.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QComboBox>

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
    QLineEdit* vertexInput;
    // QPushButton* addVertexButton;

    // edge inputs
    QLineEdit* edgeInput;
    // QPushButton* addEdgeButton;

    // face inputs
    QLineEdit* faceEdgeInput;
    // QPushButton* addFaceButton;

    // extrusion face selection and height input
    int selectedFaceIndex = -1;
    QLineEdit* extrudeHeightInput;

    // revolve inputs
    QLineEdit* revolveAngleInput;
    QLineEdit* revolveAxisInput; // axis of revolution will be an edge (future use)

    QLineEdit* booleanFacesInput;
    QComboBox* booleanOpSelector;
    

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

    void applyBooleanOperation();

signals:
    void vertexAdded();
    void edgeAdded();
    void faceAdded();
    void solidAdded();
};