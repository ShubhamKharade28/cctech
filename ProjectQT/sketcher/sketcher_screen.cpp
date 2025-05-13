
#include "sketcher_screen.h"
#include "boolean2d.h"

#include <QHBoxLayout>
#include <QStringList>
#include <QDebug>
#include <QRegularExpression>

SketcherScreen::SketcherScreen(QWidget* parent) : QWidget(parent) {
    setupUI();
}

SketcherScreen::~SketcherScreen() {
    delete sketch; 
    delete renderer;
}

void SketcherScreen::setupUI() {
    // create a horizontal layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    // create a sketcher and renderer
    sketch = new Sketcher();
    renderer = new SketchRenderer(this, sketch);
   
    // add the renderer to the layout
    layout->addWidget(renderer, 8);

    // add the sidebar to the layout
    auto* sidebarWidget = new QWidget(this);
    auto* sidebar = new QVBoxLayout(sidebarWidget);
    layout->addWidget(sidebarWidget, 2);

    setupSidebarUI(sidebar);
}

void SketcherScreen::setupSidebarUI(QVBoxLayout* sidebar) {
    // Vertex inputs
    vertexInput = new QLineEdit(this);
    auto* vertexLabel = new QLabel("Vertex Coordinates (x y z):", this);
    QPushButton* addVertexButton = new QPushButton("Add Vertex", this);
    sidebar->addWidget(vertexLabel);
    sidebar->addWidget(vertexInput);
    sidebar->addWidget(addVertexButton);
    sidebar->addStretch();
    connect(addVertexButton, &QPushButton::clicked, this, &SketcherScreen::addVertex);

    // Edge inputs
    auto* edgeLabel = new QLabel("Edge Vertices (startIndex endIndex):", this);
    edgeInput = new QLineEdit(this);
    QPushButton* addEdgeButton = new QPushButton("Add Edge", this);
    sidebar->addWidget(edgeLabel);
    sidebar->addWidget(edgeInput);
    sidebar->addWidget(addEdgeButton);
    sidebar->addStretch();
    connect(addEdgeButton, &QPushButton::clicked, this, &SketcherScreen::addEdge);

    // Face inputs
    auto* faceInputLabel = new QLabel("Add Face (space separated edges):", this);
    faceEdgeInput = new QLineEdit(this);
    QPushButton* addFaceButton = new QPushButton("Add Face", this);
    sidebar->addWidget(faceInputLabel);
    sidebar->addWidget(faceEdgeInput);
    sidebar->addWidget(addFaceButton);
    sidebar->addStretch();
    connect(addFaceButton, &QPushButton::clicked, this, &SketcherScreen::addFace);

    // List of vertices
    auto* vertexListLabel = new QLabel("Vertices:", this);
    vertexListWidget = new QListWidget(this);
    sidebar->addWidget(vertexListLabel);
    sidebar->addWidget(vertexListWidget);
    connect(this, &SketcherScreen::vertexAdded, this, &SketcherScreen::updateVertexList);

    // List of edges
    auto* edgeListLabel = new QLabel("Edges:", this);
    edgeListWidget = new QListWidget(this);
    sidebar->addWidget(edgeListLabel);
    sidebar->addWidget(edgeListWidget);
    sidebar->addStretch();
    connect(this, &SketcherScreen::edgeAdded, this, &SketcherScreen::updateEdgeList);

    // List of faces
    auto* faceListLabel = new QLabel("Faces:", this);
    faceListWidget = new QListWidget(this);
    sidebar->addWidget(faceListLabel);
    sidebar->addWidget(faceListWidget);
    sidebar->addStretch();
    connect(this, &SketcherScreen::faceAdded, this, &SketcherScreen::updateFaceList);
    connect(faceListWidget, &QListWidget::itemClicked, this, selectFace);

    // Extrude height, and extrude face button
    extrudeHeightInput = new QLineEdit(this);
    extrudeHeightInput->setPlaceholderText("Extrude Height");
    QPushButton* extrudeFaceButton = new QPushButton("Extrude Face", this);
    sidebar->addWidget(extrudeHeightInput);
    sidebar->addWidget(extrudeFaceButton);
    sidebar->addStretch();
    connect(extrudeFaceButton, &QPushButton::clicked, this, &SketcherScreen::extrudeFace);

    // Revolve angle, and revolve face button
    revolveAngleInput = new QLineEdit(this);
    revolveAngleInput->setPlaceholderText("Revolve Angle (degrees)");
    QPushButton* revolveFaceButton = new QPushButton("Revolve Face", this);
    sidebar->addWidget(revolveAngleInput);
    sidebar->addWidget(revolveFaceButton);
    sidebar->addStretch();
    connect(revolveFaceButton, &QPushButton::clicked, this, &SketcherScreen::revolveFace);

    // List of solids
    auto* solidListLabel = new QLabel("Solids:", this);
    solidListWidget = new QListWidget(this);
    sidebar->addWidget(solidListLabel);
    sidebar->addWidget(solidListWidget);
    connect(this, &SketcherScreen::solidAdded, this, &SketcherScreen::updateSolidList);

    connect(renderer, &SketchRenderer::sketchUpdated, this, [this]() {
        emit vertexAdded();
        emit edgeAdded();
        emit faceAdded();
        emit solidAdded();
    });

    // BOOLEAN OPERATIONS
    auto* booleanLabel = new QLabel("Boolean Operations", this);
    booleanFacesInput = new QLineEdit(this);
    booleanFacesInput->setPlaceholderText("Face Indices (e.g. 0 1)");
    booleanOpSelector = new QComboBox(this);
    booleanOpSelector->addItem("Union");
    booleanOpSelector->addItem("Intersection");
    booleanOpSelector->addItem("Difference");
    QPushButton* booleanOpButton = new QPushButton("Apply Boolean Operation", this);

    sidebar->addWidget(booleanLabel);
    sidebar->addWidget(booleanFacesInput);
    sidebar->addWidget(booleanOpSelector);
    sidebar->addWidget(booleanOpButton);

    connect(booleanOpButton, &QPushButton::clicked, this, applyBooleanOperation);
}

void SketcherScreen::addVertex() {
    QStringList parts = vertexInput->text().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (parts.size() != 3) {
        qDebug() << "Invalid input! Enter 3 space-separated values.";
        return;
    }

    bool xOk, yOk, zOk;
    double x = parts[0].toDouble(&xOk);
    double y = parts[1].toDouble(&yOk);
    double z = parts[2].toDouble(&zOk);

    if (xOk && yOk && zOk) {
        sketch->addVertex(x, y, z);
        renderer->update();
        emit vertexAdded();
        qDebug() << "Vertex added:" << x << y << z;
    } else {
        qDebug() << "Invalid vertex coordinates!";
    }

    vertexInput->clear();
    vertexInput->setFocus();
}

void SketcherScreen::addEdge() {
    QStringList parts = edgeInput->text().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (parts.size() != 2) {
        qDebug() << "Invalid input! Enter 2 space-separated indices.";
        return;
    }

    bool startOk, endOk;
    int startIndex = parts[0].toInt(&startOk);
    int endIndex = parts[1].toInt(&endOk);

    if (startOk && endOk) {
        sketch->addEdge(startIndex, endIndex);
        renderer->update();
        emit edgeAdded();
        qDebug() << "Edge added between indices:" << startIndex << "and" << endIndex;
    } else {
        qDebug() << "Invalid edge vertex indices!";
    }

    edgeInput->clear();
    edgeInput->setFocus();
}

void SketcherScreen::addFace() {
    QStringList edgeIndices = faceEdgeInput->text().split(" ", Qt::SkipEmptyParts);
    vector<int> edges;
    qDebug() << "Adding face with edges: ";
    for (const auto& index : edgeIndices) {
        bool ok;
        int edgeIndex = index.toInt(&ok);
        if (ok) {
            edges.push_back(edgeIndex);
            qDebug() << edgeIndex;

        } else {
            qDebug() << "Invalid edge index:" << index;
            return;
        }
    }

    sketch->addFace(edges);
    renderer->update();
    emit faceAdded();

    faceEdgeInput->clear();
    faceEdgeInput->setFocus();
    faceEdgeInput->selectAll();
    // solidListWidget->clear();
}

void SketcherScreen::addSolid() {

}

void SketcherScreen::updateVertexList() {
    vertexListWidget->clear();
    auto vertices = sketch->getVertices();
    for (int i=0; i<vertices.size(); i++) {
        auto vertex = vertices[i];
        auto x = vertex->getX(), y = vertex->getY(), z = vertex->getZ();
        QListWidgetItem* item = new QListWidgetItem(QString::number(i) + ": (" + QString::number(x) + ", " + QString::number(y) + ", " + QString::number(z) + ")");
        vertexListWidget->addItem(item);
    }
    // edgeListWidget->clear()
}

void SketcherScreen::updateEdgeList() {
    edgeListWidget->clear();
    auto edges = sketch->getEdges();
    for (int i=0; i<edges.size(); i++) {
        auto edge = edges[i];
        auto start = edge->getStart(), end = edge->getEnd();
        
        int startIdx = sketch->findVertex(start);
        int endIdx = sketch->findVertex(end);

        auto* item = new QListWidgetItem(QString::number(i) + ": (" + QString::number(startIdx) + ", " + QString::number(endIdx) + ")");
        edgeListWidget->addItem(item);
    }
    // faceListWidget->clear()
}

void SketcherScreen::updateFaceList() {
    faceListWidget->clear();
    auto faces = sketch->getFaces();
    for (int i=0; i<faces.size(); i++) {
        auto face = faces[i];
        auto edges = face->getEdges();

        QString str = QString::number(i) + ": ";
        
        for(auto& edge : edges){
            int edgeIdx = sketch->findEdge(edge);
            str += QString::number(edgeIdx) + ", ";
        }

        auto* item = new QListWidgetItem(str);
        faceListWidget->addItem(item);
    }
}

void SketcherScreen::updateSolidList() {
    solidListWidget->clear();
    auto solids = sketch->getSolids();
    for (int i=0; i<solids.size(); i++) {
        auto solid = solids[i];
        auto faces = solid->getFaces();

        QString str = QString::number(i) + ": ";
        
        for(auto& face : faces){
            int faceIdx = sketch->findFace(face);
            str += QString::number(faceIdx) + ", ";
        }

        auto* item = new QListWidgetItem(str);
        solidListWidget->addItem(item);
    }
}

void SketcherScreen::selectFace(QListWidgetItem* item) {
    int index = faceListWidget->row(item);
    if (index >= 0 && index < sketch->getFaces().size()) {
        selectedFaceIndex = index;
    } else {
        qDebug() << "Invalid face selection!";
    }
}

void SketcherScreen::extrudeFace() {
    bool heightOk;
    double height = extrudeHeightInput->text().toDouble(&heightOk);

    if (heightOk) {
        if (selectedFaceIndex != -1) {
            auto face = sketch->getFaces()[selectedFaceIndex];
            sketch->extrudeFace(face, height);
            renderer->update();
            emit solidAdded();
            emit faceAdded();
            emit edgeAdded();
            emit vertexAdded();
        } else {
            qDebug() << "No face selected for extrusion!";
        }
    } else {
        qDebug() << "Invalid extrusion height!";
    }

    extrudeHeightInput->clear();
    extrudeHeightInput->setFocus();
    extrudeHeightInput->selectAll();
}

void SketcherScreen::revolveFace() {
    bool angleOk;
    double angle = revolveAngleInput->text().toDouble(&angleOk);

    if (angleOk) {
        if (selectedFaceIndex != -1) {
            auto face = sketch->getFaces()[selectedFaceIndex];
            sketch->revolveFace(face, angle, 36); // 36 steps for a full revolution
            renderer->update();
            emit solidAdded();
            emit faceAdded();
            emit edgeAdded();
            emit vertexAdded();
        } else {
            qDebug() << "No face selected for revolution!";
        }
    } else {
        qDebug() << "Invalid revolution angle!";
    }

    revolveAngleInput->clear();
    revolveAngleInput->setFocus();
    revolveAngleInput->selectAll();
    // revolveAxisInput->clear(); // for future use
}

void SketcherScreen::applyBooleanOperation() {
    QStringList indices = booleanFacesInput->text().split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (indices.size() != 2) {
        qDebug() << "Enter exactly two face indices!";
        return;
    }
    bool ok1, ok2;
    int idx1 = indices[0].toInt(&ok1);
    int idx2 = indices[1].toInt(&ok2);
    if (!ok1 || !ok2) {
        qDebug() << "Invalid face indices!";
        return;
    }

    QString op = booleanOpSelector->currentText();
    BooleanType booleanType;
    if(op == "Union") booleanType = BooleanType::Union;
    else if(op == "Intersection") booleanType = BooleanType::Intersection;
    else booleanType = BooleanType::Difference;

    // TODO: Implement your boolean operation logic here
    qDebug() << "Applying boolean operation:" << op << "between faces" << idx1 << "and" << idx2;
    int newFaceIdx = sketch->performBooleanOperation(idx1, idx2, booleanType);

    // renderer->setHighlightedFace(newFaceIdx);
    renderer->update();
}