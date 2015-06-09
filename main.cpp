#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qsrand( QTime::currentTime().msec() );
    MainWindow w;
    w.show();

    return app.exec();
}
