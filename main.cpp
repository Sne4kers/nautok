#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("font-size: 16px");
    w.show();

    return a.exec();
}
