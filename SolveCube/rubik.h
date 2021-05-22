#ifndef RUBIK_H
#define RUBIK_H

#include <QMainWindow>
#include <QtGlobal>
#include <QPushButton>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class rubik; }
QT_END_NAMESPACE

class rubik : public QMainWindow
{
    Q_OBJECT

public:
    rubik(QWidget *parent = nullptr);
    ~rubik();

    QOpenGLWidget *Widget;
private slots:
     /*! Napravi random cube*/
    void make_random_cube();
/*! Nova igra*/
    void new_game();
    /*! Resi rubikovu kocku*/
    void solve_it();
 /*! Zanimljivosti o rubikovoj kocki*/
    void on_FunFacts_clicked();
    /*! cross patern*/
    void cross_ptn();
    /*! checkerboard patern*/
    void checker_ptn();
    /*! God's number patern*/
    void god_ptn();
    /*! six spots patern*/
    void spots_ptn();
    /*! cube in cube patern*/
    void cube_in_cube_ptn();

private:
    Ui::rubik *ui;
};
#endif // RUBIK_H
