#include "rubik.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QProcess>

rubik::rubik(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    QGridLayout *gd=new QGridLayout(ui.rubick_group_box);
    Widget=new GLWidget(ui.rubick_group_box);
    gd->addWidget(Widget);
    Widget->show();
    Widget->setFocusPolicy(Qt::StrongFocus);
    Widget->setFocus();

    // Connect button signal to appropriate slot
    connect(ui.make_cube_btn, SIGNAL (clicked()), Widget, SLOT (make_random_cube()));
    connect(ui.new_game_btn, SIGNAL (clicked()), Widget, SLOT (new_game()));
    connect(ui.solve_it_btn, SIGNAL (clicked()), Widget, SLOT (solve_it()));

}
rubik::~rubik()
{}

void rubik::make_random_cube(){
    GLWidget w;
    w.RandomCube();

}

void rubik::new_game(){
    GLWidget w;
    w.new_game();
}


void rubik::solve_it(){
    GLWidget w;
    w.solve_it();
}

