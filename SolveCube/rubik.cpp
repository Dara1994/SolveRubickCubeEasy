#include "rubik.h"
#include "./ui_rubik.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QProcess>
#include <QRandomGenerator>
#include <QtOpenGLWidgets/QtOpenGLWidgets>

rubik::rubik(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::rubik)
{
    ui->setupUi(this);
    QGridLayout *gd =new QGridLayout(ui->rubick_group_box);
    Widget = new QOpenGLWidget(ui->rubick_group_box);
    gd->addWidget(Widget);
    Widget->show();
    Widget->setFocusPolicy(Qt::StrongFocus);
    Widget->setFocus();

    // Connect button signal to appropriate slot
    connect(ui->make_cube_btn, SIGNAL (clicked()), Widget, SLOT (make_random_cube()));
    connect(ui->new_game_btn, SIGNAL (clicked()), Widget, SLOT (new_game()));
    connect(ui->solve_it_btn, SIGNAL (clicked()), Widget, SLOT (solve_it()));
    connect(ui->god_btn, SIGNAL (clicked()), Widget, SLOT (god_ptn()));
    connect(ui->six_spots_btn, SIGNAL (clicked()), Widget, SLOT (spots_ptn()));
    connect(ui->checkerboard_btn, SIGNAL (clicked()), Widget, SLOT (checker_ptn()));
    connect(ui->cross_btn, SIGNAL (clicked()), Widget, SLOT (cross_ptn()));
    connect(ui->cube_in_cube_btn, SIGNAL (clicked()), Widget, SLOT (cube_in_cube_ptn()));

}

rubik::~rubik()
{
    delete ui;
}

void rubik::make_random_cube(){
    GLWidget w;
    w.RandomCube();

}
/*! Realizacija
 * @param w nam sluzi da bi mogli da pozovemo metodu new_game
 *
 */

void rubik::new_game(){
    GLWidget w;
    w.new_game();
}

/*! Realizacija
 * @param w nam sluzi da bi mogli da pozovemo metodu solve_it
 *
 */
void rubik::solve_it(){
    GLWidget w;
    w.solve_it();
}

/*! Realizacija
 * @param number imamo deset zanimljivih cinenjica
 * @param value nasumicna vrednost
 *
 * U switchu prosledujemo value i u zavisnosti od nje nasumicno biramo jednu cienicu za prikaz u QmessegeBox.
 */
void rubik::on_FunFacts_clicked()
{
    int number=10;
    int value= QRandomGenerator::global()->generate()%number;

    switch(value){
    case 0:
    QMessageBox::information(this,"Fun fun fun", "A Rubik’s Cube has 43,252,003,274,489,856,000 possible configurations.");
        break;
    case 1:
    QMessageBox::information(this,"Fun fun fun", "If you turned Rubik’s Cube once every second it would take you 1400 TRILLION YEARS to finish to go through all the configurations.");
        break;
    case 2:
    QMessageBox::information(this,"Fun fun fun", "The best speed cubers* can solve the cube in under six seconds. And you are not one of them?");
        break;
    case 3:
    QMessageBox::information(this,"Fun fun fun", "The current world record holder is Mats Valk from the Netherlands. Who completed the puzzle in 5.55 seconds.");
        break;
    case 4:
    QMessageBox::information(this,"Fun fun fun", "Someone took 28.80 seconds to solve the puzzle BLINDFOLDED!");
        break;
    case 5:
    QMessageBox::information(this,"Fun fun fun", "The first annual International Rubik’s Championships were held in 1982.");
        break;
    case 6:
    QMessageBox::information(this,"Fun fun fun", "The world’s largest Rubik’s Cube is located in Knoxville, Tennessee. It is three metres tall and weighs over 500kg.");
        break;
    case 7:
    QMessageBox::information(this,"Fun fun fun", "The smallest cube is 10mm wide and was made by Russian Evgeniy Grigoriev.");
        break;
    case 8:
    QMessageBox::information(this,"Fun fun fun", "The most expensive cube ever produced is the Masterpiece Cube, created by Diamond Cutters International in 1995.");
        break;
    case 9:
    QMessageBox::information(this,"Fun fun fun", "Rubik’s Cube is 40 years old!");
        break;
        }

}
/*! Realizacija
 * @param w sluzi za poziv funkcije Cross()*/
void rubik::cross_ptn(){
    GLWidget w;
    w.cross_ptn();
}
/*! Realizacija
 * @param w sluzi za poziv funkcije Checker()*/
void rubik::checker_ptn(){
    GLWidget w;
    w.checker_ptn();
}
/*! Realizacija
 * @param w sluzi za poziv funkcije Number()*/
void rubik::god_ptn(){
    GLWidget w;
    w.god_ptn();
}
/*! Realizacija
 * @param w sluzi za poziv funkcije Spots()*/
void rubik::spots_ptn(){
    GLWidget w;
    w.spots_ptn();
}
/*! Realizacija
 * @param w sluzi za poziv funkcije CubeinCube()*/
void rubik::cube_in_cube_ptn(){
    GLWidget w;
    w.cube_in_cube_ptn();
}
