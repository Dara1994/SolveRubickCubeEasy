/*! \header mainwindow.h "mainwindow.h"
 * \brief Klasa GLWidget
 *
 * Definisana Clasa GLWidget koja nasleduje QLWidget. Ovde se nalaze funkcije
 * koje reaguju na desavanja misa i tastature. Takodje imamofunkcije za crtanje i
 * Randomiranje rubikove kocke. ??? ??? ???
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pokreti.h"
#include <QGLWidget>
#include <QMouseEvent>




 class GLWidget : public QGLWidget
 {
     Q_OBJECT

 public:
     /*! \brief Konstruktor.
      *@param[in] parent po default je 0.
      */
     GLWidget(QWidget *parent = 0);
     /*! Destruktor*/
     ~GLWidget();
    /*! Minimalna velicina prozora*/
     QSize minimumSizeHint() const;
     /*! Pocetna velicina prozora*/
     QSize sizeHint() const;

/*! Randomiranje rubikove kocke*/
void RandomCube();

 protected:
    /*! Desavanja na pritisak misa*/
     void mousePressEvent(QMouseEvent *event);
     /*! Desavanja na pomer misa*/
     void mouseMoveEvent(QMouseEvent *event);
    /*! Inicializacija okruzenja*/
     void initializeGL();
     /*! prostor za crtanje ??? ??? ???*/
     void paintGL();
     /*! \brief Promena velicine prozora
      *@param[in] weigth,heigth nove velicine za prozor
      */
     void resizeGL(int width, int height);
     /*! \brief Dogadjaji na pritisak dugmeta sa tastature
      *@param[in] event ??? ??? ???
      */
     void keyPressEvent( QKeyEvent * event );

 private:
     /*! Pravljene objekta i isrtavanje ??? ??? ??? */
     GLuint makeObject();

     QPoint lastPos; /*!< Poslednja posicija ??? ??? ???*/
 };

 #endif
