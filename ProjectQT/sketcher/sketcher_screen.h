#pragma once 

#include "sketcher.h"

#include <QWidget>

class SketcherScreen : public QWidget {
    Q_OBJECT

    private:
    Sketcher* sketch;

    public:
    SketcherScreen(QWidget* parent = nullptr);
};