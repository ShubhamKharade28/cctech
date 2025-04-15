#pragma once
#include <QWidget>

#include "scene.h"

class TransformationSideBar : public QWidget {
    Q_OBJECT

    Scene* scene;

public:
    explicit TransformationSideBar(QWidget* parent = nullptr, Scene* scene = nullptr);
};
