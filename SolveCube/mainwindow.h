#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QMouseEvent>

class GLWidget : public QOpenGLWidget
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


    /*! \brief  LD - left side down /levu kolonu nadole

    */
     void rotLD(int flag=0);
     /*! \brief  LD - left side up /levu kolonu nagore

     */
     void rotLU(int flag=0);
     /*! \brief  RD - right side down /desnu kolonu nadole

     */
     void rotRD(int flag=0);
     /*! \brief RU - right side up / desno kolonu nagore
*/
     void rotRU(int flag=0);
     /*! \brief   FR - front face right / nalicje rotiraj nadesno
     */
     void  rotFR(int flag=0);
     /*! \brief  TL - top row rigth /gornji red nadesno*/
     void  rotTL(int flag=0);
     /*! \brief  TL - top row left /gornji red nalevo*/
     void  rotTR(int flag=0);
/*! \brief  DL - down row left /donji red nalevo*/
     void rotDL(int flag=0);
     /*! \brief  DR - down row right /donji red nadesno*/
     void rotDR(int flag=0);
     /*! \brief  FL - front face left / nalicje rotiraj nalevo */
     void rotFL(int flag=0);
     /*! \brief  BL - back face left / zadnji deo rotiraj nalevo */
     void rotBL(int flag=0);
     /*! \brief  BR - back face left / zadnji deo rotiraj nadesno */
     void rotBR(int flag=0);


  /*! Randomiranje rubikove kocke*/
    void RandomCube();
    /*! Simple Solve metoda*/
    void SolveSimple();
    void Solver();


      protected:
         /*! Desavanja na pritisak misa*/
          void mousePressEvent(QMouseEvent *event);
          /*! Desavanja na pomer misa*/
          void mouseMoveEvent(QMouseEvent *event);
         /*! Inicializacija okruzenja*/
          void initializeGL();
          /*! Crtanje OpenGL scene. Poziva se svaki put kad widget treba da se updateuje.*/
          void paintGL();
          /*! \brief Promena velicine prozora
           *@param[in] weigth,heigth nove velicine za prozor
           */
          void resizeGL(int width, int height);
          /*! \brief Dogadjaji na pritisak dugmeta sa tastature
           *@param[in] event rotacija delova kocke
           */
          void keyPressEvent( QKeyEvent * event );





public slots:
          /*! funkcije povezane sa new game button*/
          void make_random_cube();
          /*! funkcija povezana sa reset button*/
          void new_game();
          /*! funkcija povezana sa solve it button*/
          void solve_it();
          /*! funkcija povezana sa cross button*/
          void cross_ptn();
          /*! funkcija povezana sa checkerboard button*/
          void checker_ptn();
          /*! funkcija povezana sa god's number button*/
          void god_ptn();
          /*! funkcija povezana sa six spots button*/
          void spots_ptn();
          /*! funkcija povezana sa sube in cube in cube */
          void cube_in_cube_ptn();


private:
           /*! Pravljene objekta i iscrtavanje*/
    GLuint makeObject();

    QPoint lastPos;
};


#endif // MAINWINDOW_H
