#ifndef RUBIK_H
#define RUBIK_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"


class rubik : public QMainWindow
{
    Q_OBJECT
public:
    rubik(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~rubik();

    QWidget *Widget;
private:
    Ui::MainWindow ui;
};

#endif // RUBIK_H
