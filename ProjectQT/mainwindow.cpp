#include "mainwindow.h"
#include "widgets/openglwidget.h"
#include "widgets/sidebarwidget.h"

#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;

    glWidget = new OpenGLWidget(this);
    sidebar = new SidebarWidget(this);

    layout->addWidget(glWidget, 3);
    layout->addWidget(sidebar, 1);

    central->setLayout(layout);
    setCentralWidget(central);
    setWindowTitle("3D Shape Editor");
}

MainWindow::~MainWindow() {}
