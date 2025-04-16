#include <QApplication>
// #include "mainwindow.h"

#include "test-window.h"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // MainWindow window;
    // window.show();

    TestWindow window;
    window.show();
 
    return app.exec();
}