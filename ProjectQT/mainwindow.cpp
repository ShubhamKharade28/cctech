#include "mainwindow.h"
// #include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    // , ui(new Ui::MainWindow)
{
    // ui->setupUi(this);

    // Example: connect a button if one exists in your .ui file
    // connect(ui->myButton, &QPushButton::clicked, this, &MainWindow::onMyButtonClicked);
}

MainWindow::~MainWindow()
{
    // delete ui;
}
