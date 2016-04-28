#include "mainwindow.h"
#include <QApplication>
#include "rubik.hpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    rubik d;
    d.show();
    return a.exec();
}
