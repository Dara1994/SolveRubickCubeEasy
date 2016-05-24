#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <QMouseEvent>

 class GLWidget : public QGLWidget
 {
     Q_OBJECT

 public:
     GLWidget(QWidget *parent = 0);
     ~GLWidget();

     QSize minimumSizeHint() const;
     QSize sizeHint() const;

      void rotLD();
      void rotLU();
      void rotRD();
      void rotRU();

      void  rotFR();
      void  rotTL();
      void  rotTR();

      void rotDL();
      void rotDR();
      void rotFL();

 protected:
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void initializeGL();
     void paintGL();
     void resizeGL(int width, int height);
     void keyPressEvent( QKeyEvent * event );

 private:
     GLuint makeObject();

     QPoint lastPos;
 };

 #endif
