#include "rubik.h"

#include <QApplication>

auto main(int argc, char *argv[]) -> int
{
    QApplication a(argc, argv);
    rubik w;
    w.show();
    return a.exec();
}
