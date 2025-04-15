#pragma once
#include <QWidget>
#include <QListWidget>

#include "scene.h"

class ShapesSideBar : public QWidget {
    Q_OBJECT
public:
    explicit ShapesSideBar(QWidget* parent = nullptr, Scene *scene = nullptr);

private slots:
    void onAddShapeClicked();

private:
    Scene* scene;
    QListWidget* shapeList;

signals:
    void sceneUpdated();
};
