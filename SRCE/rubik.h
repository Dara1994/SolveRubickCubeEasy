/*! \header.h rubik.h "rubik.h"
 *  \brief Class rubik.
 *
 * Sadrzi Klasu rubik koja nasledjuje QMainWindow. ??? ??? ???
 */
#ifndef RUBIK_H
#define RUBIK_H

#include <QtWidgets/QMainWindow>
#include <QGLWidget>
#include "ui_rubik.h"

class rubik : public QMainWindow
{
    Q_OBJECT

public:
    /*! \brief Konstruktor za rubik.
     *@param[in] parent po default je 0.
     *@param[in] flags po defaultu je 0.
     */
    rubik(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    /*! Destruktor za rubik.*/
    ~rubik();

    QGLWidget *Widget; /*!< pokazivac klase Widget. */
private:
    Ui::MainWindow ui; /*!< ??? ??? ???*/
};

#endif
