#pragma once
#include <QWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>

#include "scene.h"

class TransformationSideBar : public QWidget {
    Q_OBJECT

public:
    explicit TransformationSideBar(QWidget* parent = nullptr, Scene* scene = nullptr);

private:
    QDoubleSpinBox *xPosition, *yPosition, *zPosition;
    QDoubleSpinBox *xRotation, *yRotation, *zRotation;
    QDoubleSpinBox *scale;
    QLabel* currentShapeLabel;
    QPushButton* applyButton;

    Scene* scene;
    int currentShapeId = -1;

    void resetTransformations();
    void getShapeTransformations();

public:
    void setCurrentShapeId(int id);
    int getCurrentShapeId();

signals:
    void transformationUpdated(); // Signal to notify when transformations are updated

private slots:
    void onApplyButtonClicked();
};
