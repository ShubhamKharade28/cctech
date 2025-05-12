#include "mainwindow.h"
#include <QApplication>
#include <QPalette>

void setStyleSheet(QApplication& app) {
    app.setStyleSheet(R"(
        QPushButton {
            background-color: #444444;
            color: white;
            border-radius: 10px;
            padding: 6px 12px;
        }
        QPushButton:hover {
            background-color: #555555;
        }
        QPushButton:pressed {
            background-color: #333333;
        }
        QComboBox {
            background-color: #444444;
            color: white;
            border-radius: 10px;
            padding: 6px 12px;
            padding-right: 30px;
        }
        QComboBox:hover {
            background-color: #555555;
        }
        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 25px;
            border-left: 1px solid #555555;
            background-color: #333333;
            border-top-right-radius: 10px;
            border-bottom-right-radius: 10px;
        }
        QComboBox::down-arrow {
            image: url(:/icons/down_arrow_white.png); 
            width: 12px;
            height: 12px;
        }
        QComboBox QAbstractItemView {
            background-color: #333333;
            color: white;
            selection-background-color: #555555;
            border-radius: 6px;
        }
    )");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // setDarkTheme(app);
    setStyleSheet(app);
    
    MainWindow window;
    window.show();
 
    return app.exec();
}