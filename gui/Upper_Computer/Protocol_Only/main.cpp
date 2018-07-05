#include "mainwindow.h"
#include <QApplication>
#include <protocol_debug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Protocol_Debug debug;
    debug.exec();

    return a.exec();
}
