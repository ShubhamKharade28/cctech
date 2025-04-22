#include "scene_creator.h"

#include <QHBoxLayout>

SceneCreator::SceneCreator(QWidget *parent): QWidget(parent) {
    auto* layout = new QHBoxLayout(this);

    scene = new Scene("My 3D Scene");

    shapesBar = new ShapesSideBar(this, scene);
    sceneRenderer = new SceneRenderer(this, scene);
    transformationBar = new TransformationSideBar(this, scene);

    layout->addWidget(shapesBar, 2);
    layout->addWidget(sceneRenderer, 6);
    layout->addWidget(transformationBar, 2);

    connect(shapesBar, &ShapesSideBar::sceneUpdated, sceneRenderer, QOverload<>::of(&QOpenGLWidget::update));
    connect(transformationBar, &TransformationSideBar::transformationUpdated, sceneRenderer, QOverload<>::of(&QOpenGLWidget::update));

    connect(shapesBar, &ShapesSideBar::shapeSelected, this, &SceneCreator::onShapeSelected);
    connect(shapesBar, &ShapesSideBar::shapeDeleted, this, &SceneCreator::onShapeDeleted);
}

void SceneCreator::onShapeSelected(int shapeId) {
    transformationBar->setCurrentShapeId(shapeId);
}

void SceneCreator::onShapeDeleted(int shapeId) {
    transformationBar->setCurrentShapeId(-1);
}