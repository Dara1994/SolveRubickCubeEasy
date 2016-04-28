#include "rubik.hpp"
#include <QtWidgets/QMainWindow>
#include <QGLWidget>
#include <QGridLayout>

rubik::rubik(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    QGridLayout *gd=new QGridLayout(ui.groupBox);
    Widget=new QGLWidget(ui.groupBox);
    gd->addWidget(Widget);
    Widget->show();
    Widget->setFocusPolicy(Qt::StrongFocus);
    Widget->setFocus();
}

rubik::~rubik()
{

}
