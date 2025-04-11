#include <QApplication>
#include <QMainWindow>
#include "myopenglwidget.h"
 
int main(int argc, char *argv[])
{

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(2, 1);  // You can adjust depending on your system
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication app(argc, argv);
 
    QMainWindow window;
    window.setWindowTitle("OpenGL Triangle");
 
    MyOpenGLWidget *openGLWidget = new MyOpenGLWidget();
    window.setCentralWidget(openGLWidget);
 
    window.resize(800, 600);
    window.show();
 
    return app.exec();
}