#pragma once
#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

#include "scene.h"

class Shape;

class ShapesSideBar : public QWidget {
    Q_OBJECT
public:
    explicit ShapesSideBar(QWidget* parent = nullptr, Scene *scene = nullptr);

private slots:
    void updateDimensionInputs(const QString& shapeType);
    void onAddShapeClicked();
    void onDeleteShapeClicked();

private:
    Scene* scene;
    QComboBox* shapeSelector;
    QFormLayout* dimensionForm;
    QPushButton* addShapeButton;
    QPushButton* deleteShapeButton;
    QListWidget* shapeList;
    map<QString, QLineEdit*> inputFields;

signals:
    void sceneUpdated();
};
