#pragma once 

#include "sketcher.h"
#include "sketch_renderer.h"

#include <QWidget>

class SketcherScreen : public QWidget {
    Q_OBJECT

    private:
    Sketcher* sketch;
    SketchRenderer* renderer;

    public:
    explicit SketcherScreen(QWidget* parent = nullptr);
    // ~SketcherScreen();
};