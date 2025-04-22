#include "shapes_sidebar.h"

#include <QVBoxLayout>
#include <QMessageBox>

#include "shape.h"
#include "shapes.h"

ShapesSideBar::ShapesSideBar(QWidget* parent, Scene *scene) : 
    QWidget(parent), scene(scene)
{
    auto* layout = new QVBoxLayout(this);

    shapeSelector = new QComboBox(this);
    shapeSelector->addItems({"Cube", "Cuboid", "Sphere", "Cylinder"});
    layout->addWidget(shapeSelector);

    dimensionForm = new QFormLayout(this);
    layout->addLayout(dimensionForm);

    addShapeButton = new QPushButton("Add Shape");
    deleteShapeButton = new QPushButton("Delete Selected Shape");
    layout->addWidget(addShapeButton);
    layout->addWidget(deleteShapeButton);

    shapeList = new QListWidget(this);
    layout->addWidget(shapeList);

    updateDimensionInputs("Cube");

    connect(shapeSelector, &QComboBox::currentTextChanged,
        this, &ShapesSideBar::updateDimensionInputs);

    connect(addShapeButton, &QPushButton::clicked, 
            this, &ShapesSideBar::onAddShapeClicked);

    connect(deleteShapeButton, &QPushButton::clicked, this, &ShapesSideBar::onDeleteShapeClicked);
    connect(shapeList, &QListWidget::itemClicked, this, &ShapesSideBar::onShapeItemSelected);
}

void ShapesSideBar::onShapeItemSelected(QListWidgetItem* item) {
    QString shapeName = item->text();
    int shapeId = shapeName.split(" ").last().toInt(); // Assuming shape name ends with ID

    emit shapeSelected(shapeId);
}

void ShapesSideBar::onDeleteShapeClicked() {
    QListWidgetItem* selectedItem = shapeList->currentItem();

    if (!selectedItem) {
        QMessageBox::warning(this, "No Shape Selected", "Please select a shape to delete.");
        return;
    }

    QString shapeName = selectedItem->text();
    int shapeId = shapeName.split(" ").last().toInt();

    scene->removeShapeById(shapeId);
    delete selectedItem;

    // Emit signal to update the scene
    emit sceneUpdated();
    emit shapeDeleted(shapeId);
}

void ShapesSideBar::onAddShapeClicked() {
    using namespace std;

    bool ok = true;
    auto get = [&](const QString& key) -> double {
        bool localOk;
        double val = inputFields[key]->text().toDouble(&localOk);
        ok = ok && localOk;
        return val;
    };

    QString selectedShape = shapeSelector->currentText();
    shared_ptr<Shape> shape;
    static int shapeId = 1;
    QString shapeName;

    if (selectedShape == "Cube") {
        double side = get("Length");
        if (ok) {
            shape = make_shared<Cube>(side);
            shapeName = "Cube " + QString::number(shapeId);
        }
    }
    else if (selectedShape == "Cuboid") {
        double l = get("Length");
        double w = get("Width");
        double h = get("Height");
        if (ok) {
            shape = make_shared<Cuboid>(l, w, h);
            shapeName = "Cuboid " + QString::number(shapeId);
        }
    }
    else if (selectedShape == "Sphere") {
        double r = get("Radius");
        if (ok) {
            shape = make_shared<Sphere>(r);
            shapeName = "Sphere " + QString::number(shapeId);
        }
    }
    else if (selectedShape == "Cylinder") {
        double r = get("Radius");
        double h = get("Height");
        if (ok) {
            shape = make_shared<Cylinder>(r, h);
            shapeName = "Cylinder " + QString::number(shapeId);
        }
    }

    // If invalid input or shape creation failed, show warning
    if (!ok || !shape) {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid numbers for all dimensions.");
        return;
    }

    // Add shape to scene and list
    scene->addShape(shape, shapeName.toStdString(), shapeId);
    shapeList->addItem(shapeName);
    shapeId++;

    emit sceneUpdated();
}


void ShapesSideBar::updateDimensionInputs(const QString& shapeType) {
    // Clear previous inputs
    QLayoutItem* child;
    while((child = dimensionForm->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    inputFields.clear();
    
    static const QMap<QString, QStringList> shapeDimensions = {
        { "Cube",     {"Length"} },
        { "Cuboid",   {"Length", "Width", "Height"} },
        { "Sphere",   {"Radius"} },
        { "Cylinder", {"Radius", "Height"} }
    };

    // Loop and create fields
    if(shapeDimensions.contains(shapeType)) {
        for(const QString& dim : shapeDimensions[shapeType]) {
            auto* field = new QLineEdit(this);
            inputFields[dim] = field;
            dimensionForm->addRow(dim + ":", field);
        }
    }
}