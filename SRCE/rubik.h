#ifndef RUBIK_H
#define RUBIK_H

#include <QtWidgets/QMainWindow>
#include <QGLWidget>
#include "ui_rubik.h"

class rubik : public QMainWindow
{
    Q_OBJECT

public:
    rubik(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~rubik();

    QGLWidget *Widget;
private:
    Ui::MainWindow ui;
};

#endif
