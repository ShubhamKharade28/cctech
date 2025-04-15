#include "transformation_sidebar.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QDoubleSpinBox>

TransformationSideBar::TransformationSideBar(QWidget* parent, Scene* scene) : QWidget(parent), scene(scene) {
    auto* layout = new QVBoxLayout(this);

    auto* transformBox = new QGroupBox("Transform");
    auto* formLayout = new QFormLayout();

    formLayout->addRow("Position X:", new QDoubleSpinBox());
    formLayout->addRow("Position Y:", new QDoubleSpinBox());
    formLayout->addRow("Position Z:", new QDoubleSpinBox());

    formLayout->addRow("Rotation X:", new QDoubleSpinBox());
    formLayout->addRow("Rotation Y:", new QDoubleSpinBox());
    formLayout->addRow("Rotation Z:", new QDoubleSpinBox());

    formLayout->addRow("Scale:", new QDoubleSpinBox());

    transformBox->setLayout(formLayout);
    layout->addWidget(transformBox);
}
