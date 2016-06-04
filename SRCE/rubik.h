/*! \header.h rubik.h "rubik.h"
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

    QGLWidget *Widget; /*!< pokazivac klase Widget. */
private slots:
    void make_random_cube();

private:
    Ui::MainWindow ui; /*!< ??? ??? ???*/
};

#endif
