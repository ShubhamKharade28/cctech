#include "model_editor.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>

#include <QtConcurrent> // to run concurrently

ModelEditor::ModelEditor(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

ModelEditor::~ModelEditor()
{
    delete sketchRenderer;
    delete sketch;
}

void ModelEditor::setupUI()
{
    sketch = new Sketcher();
    sketchRenderer = new SketchRenderer(this, sketch);
    // Set up the UI layout and other components here

    // Buttons
    QPushButton* openButton = new QPushButton("Open File", this);
    QPushButton* exportObjButton = new QPushButton("Export OBJ", this);
    QPushButton* exportStlButton = new QPushButton("Export STL", this);
    QPushButton* clearButton = new QPushButton("Clear Sketch", this);

    // Top Button Layout
    QHBoxLayout* topButtonsLayout = new QHBoxLayout();
    topButtonsLayout->addWidget(openButton);
    topButtonsLayout->addWidget(exportObjButton);
    topButtonsLayout->addWidget(exportStlButton);
    topButtonsLayout->addWidget(clearButton);
    topButtonsLayout->addStretch();
    
    // Main Layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topButtonsLayout);
    mainLayout->addWidget(sketchRenderer);
    setLayout(mainLayout);

    // TODO: Connect signals 
    connect(openButton, &QPushButton::clicked, this, &ModelEditor::onOpenFileClicked);
    connect(exportObjButton, &QPushButton::clicked, this, &ModelEditor::onExportObjClicked);
    connect(exportStlButton, &QPushButton::clicked, this, &ModelEditor::onExportStlClicked);
    connect(clearButton, &QPushButton::clicked, this, &ModelEditor::onClearSketchClicked);
}

void ModelEditor::onOpenFileClicked() 
{
    // open stl or obj file
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), "", tr("STL Files (*.stl);;OBJ Files (*.obj)"));
    if (fileName.isEmpty()) return;

    sketch->clear();

    string stdFileName = fileName.toStdString();

    // if (fileName.endsWith(".stl", Qt::CaseInsensitive)) {
    //     sketch->loadSketchFromSTL(stdFileName);
    // } else if (fileName.endsWith(".obj", Qt::CaseInsensitive)) {
    //     sketch->loadSketchFromOBJ(stdFileName);
    // }
    // 
    // sketchRenderer->update();

    QtConcurrent::run([=]() {
        if (fileName.endsWith(".stl", Qt::CaseInsensitive)) {
            sketch->loadSketchFromSTL(stdFileName);
        } else if (fileName.endsWith(".obj", Qt::CaseInsensitive)) {
            sketch->loadSketchFromOBJ(stdFileName);
        }

        QMetaObject::invokeMethod(sketchRenderer, "update", Qt::QueuedConnection);
    });

    
}

void ModelEditor::onExportObjClicked() 
{
    
}

void ModelEditor::onExportStlClicked() 
{

}

void ModelEditor::onClearSketchClicked() 
{
    // sketch->clear();
    // sketchRenderer->update();

    QtConcurrent::run([this]() {
        sketch->clear();
        QMetaObject::invokeMethod(sketchRenderer, "update", Qt::QueuedConnection);
    });
}