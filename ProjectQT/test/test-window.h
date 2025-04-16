#pragma once

#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>

#include "point.h"
#include "bezier_curve.h"

#include "sidebar.h"
#include "renderer.h"

#include <bits/stdc++.h>
using namespace std;

class TestWindow : public QWidget {
    Q_OBJECT

public:
    TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    Sidebar* sidebar;
    Renderer* renderer;

    BezierCurve* curve;
};
