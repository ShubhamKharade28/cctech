#pragma once

#include <QMainWindow>
#include <QTimer>

// This includes the full definition of the UI class generated from mainwindow.ui
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// private:
//     Ui::MainWindow *ui;
};