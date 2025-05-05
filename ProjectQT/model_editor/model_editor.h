#pragma once 

#include "sketch_renderer.h"

#include <QWidget>

class ModelEditor : public QWidget
{
    Q_OBJECT
public: 
    explicit ModelEditor(QWidget *parent = nullptr);
    ~ModelEditor() override;

private:
    void setupUI();

    Sketcher* sketch;
    SketchRenderer* sketchRenderer;

private slots:
    void onOpenFileClicked();
    void onExportObjClicked();
    void onExportStlClicked();
    void onClearSketchClicked();
};