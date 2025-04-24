#pragma once 

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class ScreenSelectorDialog : public QDialog {
    Q_OBJECT
public:
    explicit ScreenSelectorDialog(QWidget *parent = nullptr);
    int getSelectedScreen();

private: 
    int selectedScreen;

private slots:
    void selectSceneCreator();
    void selectBezierSketcher();
    void selectSketcher();
};