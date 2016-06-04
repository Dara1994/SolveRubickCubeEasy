/*! \file main.cpp
 * \brief Main funkcija
 */
#include <QtWidgets/QApplication>
#include "rubik.h"

/*! Main funkcija
 * @param w nasa rubikova kocka.
 *
 * Prikazuje nasu rubikovu kocku, ??? ??? ???
 * i na kraju vraca a.exe kao izvrsnu aplikaciju
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rubik w;
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
