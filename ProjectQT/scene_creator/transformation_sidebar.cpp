#include "transformation_sidebar.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QDoubleSpinBox>

#include <QDebug>

TransformationSideBar::TransformationSideBar(QWidget* parent, Scene* scene) : QWidget(parent), scene(scene) {
    auto* layout = new QVBoxLayout(this);

    auto* transformBox = new QGroupBox("Transform");
    auto* formLayout = new QFormLayout();

    xPosition = new QDoubleSpinBox();
    yPosition = new QDoubleSpinBox();
    zPosition = new QDoubleSpinBox();

    xRotation = new QDoubleSpinBox();   
    yRotation = new QDoubleSpinBox();
    zRotation = new QDoubleSpinBox();

    scale = new QDoubleSpinBox();

    // Set range for position spin boxes
    xPosition->setRange(-100.0, 100.0);
    yPosition->setRange(-100.0, 100.0);
    zPosition->setRange(-100.0, 100.0);

    // Set range for rotation spin boxes
    xRotation->setRange(-360.0, 360.0);
    yRotation->setRange(-360.0, 360.0);
    zRotation->setRange(-360.0, 360.0);

    // Set range for scale spin box
    scale->setRange(-10.0, 10.0);

    formLayout->addRow("Position X:", xPosition);
    formLayout->addRow("Position Y:", yPosition);
    formLayout->addRow("Position Z:", zPosition);

    formLayout->addRow("Rotation X:", xRotation);
    formLayout->addRow("Rotation Y:", yRotation);
    formLayout->addRow("Rotation Z:", zRotation);

    formLayout->addRow("Scale:", scale);

    transformBox->setLayout(formLayout);
    layout->addWidget(transformBox);

    currentShapeLabel = new QLabel("Current Shape ID: None", this);
    layout->addWidget(currentShapeLabel);

    applyButton = new QPushButton("Apply Transformations", this);
    layout->addWidget(applyButton);

    connect(applyButton, &QPushButton::clicked, this, &TransformationSideBar::onApplyButtonClicked);
}

void TransformationSideBar::onApplyButtonClicked() {
    if (currentShapeId == -1) return;

    DrawableShape* shape = scene->getShapeById(currentShapeId);
    if (shape) {
        double xRotationValue = xRotation->value();
        double yRotationValue = yRotation->value();
        double zRotationValue = zRotation->value();

        shape->setPosition({xPosition->value(), yPosition->value(), zPosition->value()});
        shape->setRotation({xRotation->value(), yRotation->value(), zRotation->value()});
        shape->setScale(scale->value());

        emit transformationUpdated(); // Emit signal to notify that transformations have been applied
    }
}

void TransformationSideBar::resetTransformations() {
    xPosition->setValue(0.0);
    yPosition->setValue(0.0);
    zPosition->setValue(0.0);

    xRotation->setValue(0.0);
    yRotation->setValue(0.0);
    zRotation->setValue(0.0);

    scale->setValue(1.0);
}

void TransformationSideBar::getShapeTransformations() {
    if (currentShapeId == -1) return;

    qDebug() << "Getting transformations for shape ID:" << currentShapeId;

    DrawableShape* shape = scene->getShapeById(currentShapeId);
    if (shape) {
        using namespace std;
        vector<double> position = shape->getPosition();
        vector<double> rotation = shape->getRotation(); 
        double scaleValue = shape->getScale();

        // qDebug() << "Rotation: " << rotation[0] << rotation[1] << rotation[2];

        xPosition->setValue(position[0]);
        yPosition->setValue(position[1]);  
        zPosition->setValue(position[2]);
        
        xRotation->setValue(rotation[0]);
        yRotation->setValue(rotation[1]);
        zRotation->setValue(rotation[2]);

        scale->setValue(scaleValue);
    }
    update();
}

void TransformationSideBar::setCurrentShapeId(int id) {
    currentShapeId = id;
    if (id == -1) {
        currentShapeLabel->setText("Current Shape ID: None!");
        resetTransformations();
    } else {
        currentShapeLabel->setText("Current Shape ID: " + QString::number(id));
        getShapeTransformations();
    }
}

int TransformationSideBar::getCurrentShapeId() {
    return currentShapeId;
}