#pragma once

#include "scene.h"
#include "shapes_sidebar.h"
#include "scene_renderer.h"
#include "transformation_sidebar.h"

#include <QWidget>

class SceneCreator : public QWidget {
    Q_OBJECT

    Scene *scene;
    ShapesSideBar *shapesBar;
    SceneRenderer *sceneRenderer;
    TransformationSideBar *transformationBar;
public:
    explicit SceneCreator(QWidget *parent = nullptr);
};