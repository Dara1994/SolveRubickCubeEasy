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


 protected:
     void initializeGL();
     void paintGL();
     void resizeGL(int width, int height);

 private:
     GLuint makeObject();
     QPoint lastPos;
 };

 #endif
