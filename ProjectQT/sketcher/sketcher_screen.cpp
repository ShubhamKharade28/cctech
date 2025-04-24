
#include "sketcher_screen.h"
#include <QHBoxLayout>

SketcherScreen::SketcherScreen(QWidget* parent) : QWidget(parent) {
    sketch = new Sketcher();

    // create a horizontal layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    
}