#include "rubik.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QGridLayout>

rubik::rubik(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    QGridLayout *gd=new QGridLayout(ui.groupBox);
    Widget=new GLWidget(ui.groupBox);
    gd->addWidget(Widget);
    Widget->show();
    Widget->setFocusPolicy(Qt::StrongFocus);
    Widget->setFocus();

    // Connect button signal to appropriate slot
    connect(ui.Make_a_cube, SIGNAL (released()), this, SLOT (handleButton()));

}

rubik::~rubik()
{}

