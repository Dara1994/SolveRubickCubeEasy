/*! \header mainwindow.h "mainwindow.h"
 * \brief Klasa GLWidget
 *
 * Definisana Clasa GLWidget koja nasleduje QLWidget. Ovde se nalaze funkcije
 * koje reaguju na desavanja misa i tastature. Takodje imamofunkcije za crtanje i
 * Randomiranje rubikove kocke. ??? ??? ???
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

     /*! * \brief Moguci pokreti rubikove kocke
 *
 * Ovde imamo sve nase pokrete.
 * Moguci pokreti su:
 * LU - left side up /levu kolonu nagore
 * LD - left side down /levu kolonu nadole
 * RU - right side up /desnu kolonu nagore
 * RD - right side down /desnu kolonu nadole
 * FR - front face right / nalicje rotiraj nadesno
 * FL - front face left / nalicije rotiraj nalevo
 * TL - top row left /gorni red nalevo
 * TR - top row right /gornji red nadesno
 * DL - down row left /donji red nalevo
 * DR - down row rigth /donji red nadesno
 *
 * Imamo konstruktor i destruktor nasledjeni od roditeljske klase.
 */
     /*! \brief  LD - left side down /levu kolonu nadole

     */
      void rotLD();
      /*! \brief  LD - left side up /levu kolonu nagore

      */
      void rotLU();
      /*! \brief  RD - right side down /desnu kolonu nadole

      */
      void rotRD();
      /*! \brief RU - right side up / desno kolonu nagore
*/
      void rotRU();
      /*! \brief   FR - front face right / nalicje rotiraj nadesno

      */
      void  rotFR();
      /*! \brief  TL - top row rigth /gornji red nadesno*/

      void  rotTL();
      /*! \brief  TL - top row left /gornji red nalevo*/
      void  rotTR();
/*! \brief  DL - down row left /donji red nalevo*/
      void rotDL();
      /*! \brief  DR - down row right /donji red nadesno*/
      void rotDR();
      /*! \brief  FL - front face left / nalicje rotiraj nalevo */
      void rotFL();


   /*! Randomiranje rubikove kocke*/
     void RandomCube();
     /*! SImple Solve metoda*/
     void SolveSimple();

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
 public slots:
           void make_random_cube();
 private:
            /*! Pravljene objekta i isrtavanje*/
     GLuint makeObject();

     QPoint lastPos;
 };

 #endif
