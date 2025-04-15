#include "shapes_sidebar.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>

#include "shapes.h"

ShapesSideBar::ShapesSideBar(QWidget* parent, Scene *scene) : QWidget(parent), scene(scene) {
    auto* layout = new QVBoxLayout(this);

    auto* addShapeButton = new QPushButton("Add Sphere");
    shapeList = new QListWidget(this);

    layout->addWidget(addShapeButton);
    layout->addWidget(shapeList);
    
    connect(addShapeButton, &QPushButton::clicked, this, &ShapesSideBar::onAddShapeClicked);
}

void ShapesSideBar::onAddShapeClicked() {
    auto shape = make_shared<Cube>(5);
    static int shapeId = 1;
    string shapeName = "Cube " + to_string(shapeId);

    scene->addShape(shape, shapeName, shapeId);

    shapeList->addItem(QString::fromStdString(shapeName));
    shapeId++;

    emit sceneUpdated();
}
