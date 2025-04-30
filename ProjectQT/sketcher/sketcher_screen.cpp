
#include "sketcher_screen.h"
#include <QHBoxLayout>

#include <QDebug>

SketcherScreen::SketcherScreen(QWidget* parent) : QWidget(parent) {
    setupUI();
}

SketcherScreen::~SketcherScreen() {
    //     delete sketch; 
    //     delete renderer;
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
    addVertexButton = new QPushButton("Add Vertex", this);
    vertexXInput = new QLineEdit(this);
    vertexYInput = new QLineEdit(this);
    vertexZInput = new QLineEdit(this);
    auto* vertexLabel = new QLabel("Vertex Coordinates (x, y, z):", this);
    sidebar->addWidget(vertexLabel);
    sidebar->addWidget(vertexXInput);
    sidebar->addWidget(vertexYInput);
    sidebar->addWidget(vertexZInput);
    sidebar->addWidget(addVertexButton);
    sidebar->addStretch();
    connect(addVertexButton, &QPushButton::clicked, this, &SketcherScreen::addVertex);

    // Edge inputs
    edgeStartInput = new QLineEdit(this);
    edgeEndInput = new QLineEdit(this);
    addEdgeButton = new QPushButton("Add Edge", this);
    auto* edgeLabel = new QLabel("Edge Vertices (start, end):", this);
    sidebar->addWidget(edgeLabel);
    sidebar->addWidget(edgeStartInput);
    sidebar->addWidget(edgeEndInput);
    sidebar->addWidget(addEdgeButton);
    sidebar->addStretch();
    connect(addEdgeButton, &QPushButton::clicked, this, &SketcherScreen::addEdge);

    // Face inputs
    auto* faceInputLabel = new QLabel("Add Face (space separated edges):", this);
    faceEdgeInput = new QLineEdit(this);
    addFaceButton = new QPushButton("Add Face", this);
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
    extrudeFaceButton = new QPushButton("Extrude Face", this);
    sidebar->addWidget(extrudeHeightInput);
    sidebar->addWidget(extrudeFaceButton);
    sidebar->addStretch();
    connect(extrudeFaceButton, &QPushButton::clicked, this, &SketcherScreen::extrudeFace);

    // List of solids
    auto* solidListLabel = new QLabel("Solids:", this);
    solidListWidget = new QListWidget(this);
    sidebar->addWidget(solidListLabel);
    sidebar->addWidget(solidListWidget);
    connect(this, &SketcherScreen::solidAdded, this, &SketcherScreen::updateSolidList);
}

void SketcherScreen::addVertex() {
    bool xOk, yOk, zOk;
    double x = vertexXInput->text().toDouble(&xOk);
    double y = vertexYInput->text().toDouble(&yOk);
    double z = vertexZInput->text().toDouble(&zOk);

    if (xOk && yOk && zOk) {
        sketch->addVertex(x, y, z);
        renderer->update();
        emit vertexAdded();

        qDebug() << "Vertex added:" << x << y << z;
    } else {
        // Handle invalid input
        qDebug() << "Invalid vertex coordinates!";
    }

    vertexXInput->clear();
    vertexYInput->clear();
    vertexZInput->clear();

    vertexXInput->setFocus();
    vertexXInput->selectAll();
}

void SketcherScreen::addEdge() {
    bool startOk, endOk;
    int start = edgeStartInput->text().toInt(&startOk);
    int end = edgeEndInput->text().toInt(&endOk);

    if (startOk && endOk) {
        sketch->addEdge(start, end);
        renderer->update(); 
        emit edgeAdded();
    } else {
        qDebug() << "Invalid edge vertices!";
    }

    edgeStartInput->clear();
    edgeEndInput->clear();

    edgeStartInput->setFocus();
    edgeStartInput->selectAll();
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