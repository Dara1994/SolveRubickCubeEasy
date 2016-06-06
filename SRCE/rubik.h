/*! \file rubik.h
 * \header.h rubik.h "rubik.h"
 *  \brief Class rubik.
 *
 * Sadrzi Klasu rubik koja nasledjuje QMainWindow. ??? ??? ???
 */
#ifndef RUBIK_H
#define RUBIK_H

#include <QtWidgets/QMainWindow>
#include <QGLWidget>
#include <QPushButton>
#include "ui_rubik.h"
#include "mainwindow.h"
/*! Klasa rubik
 * Sadrzi konstruktor i destruktor. Kao i metode za pravljene nove, randominizaciju, resertovane i zanimlivosti
 * o rubikovoj kocki.
 */
class rubik : public QMainWindow
{
    Q_OBJECT

public:
    /*! \brief Konstruktor za rubik.
     *@param[in] parent po default je 0.
     *@param[in] flags po defaultu je 0.
     */
   explicit rubik(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    /*! Destruktor za rubik.*/
    ~rubik();

    /*! pokazivac klase Widget. */
     QGLWidget *Widget;
private slots:
     /*! Napravi random cube*/
    void make_random_cube();
/*! Nova igra*/
    void new_game();
    /*! Resi rubikovu kocku*/
    void solve_it();
 /*! Zanimljivosti o rubikovoj kocki*/
    void on_FunFacts_clicked();

private:
    /*! pomocu ovog polja mozemo da pristupimo i menjamo fajl .ui iz ove klase*/
     Ui::MainWindow ui;
};

#endif
