#pragma once

#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>

#include "point.h"
#include "bezier_curve.h"

#include "bezier_sidebar.h"
#include "bezier_renderer.h"

#include <bits/stdc++.h>
using namespace std;

class BezierSketcher : public QWidget {
    Q_OBJECT

public:
    BezierSketcher(QWidget *parent = nullptr);
    ~BezierSketcher();

private:
    BezierSidebar* sidebar;
    BezierRenderer* renderer;

    BezierCurve* curve1;
    BezierCurve* curve2;
};
