#pragma once 

#include <QWidget>

#include "sketcher.h"
#include "bezier_curve.h"
#include "scene.h"

class MainScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MainScreen(QWidget *parent = nullptr);
    ~MainScreen() override;    

    

};