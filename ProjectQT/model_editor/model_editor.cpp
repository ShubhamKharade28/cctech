#include "model_editor.h"

#include <QVBoxLayout>

ModelEditor::ModelEditor(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
}

void ModelEditor::setupUI()
{
    sketch = new Sketcher(this);
    sketchRenderer = new SketchRenderer(this, sketch);
    // Set up the UI layout and other components here

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(sketchRenderer);

    
}