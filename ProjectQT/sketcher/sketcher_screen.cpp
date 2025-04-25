
#include "sketcher_screen.h"
#include <QHBoxLayout>

SketcherScreen::SketcherScreen(QWidget* parent) : QWidget(parent) {
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
}

// SketcherScreen::~SketcherScreen() {
// //     delete sketch; // Cleanup if needed
// //     delete renderer; // Cleanup if needed
// }

