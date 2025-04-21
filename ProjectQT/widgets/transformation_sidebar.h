#pragma once
#include <QWidget>
#include <QDoubleSpinBox>

#include "scene.h"

class TransformationSideBar : public QWidget {
    Q_OBJECT

    Scene* scene;

public:
    explicit TransformationSideBar(QWidget* parent = nullptr, Scene* scene = nullptr);

private:
    QDoubleSpinBox *xPosition, *yPosition, *zPosition;
    QDoubleSpinBox *xRotation, *yRotation, *zRotation;
    QDoubleSpinBox *scale;
};
