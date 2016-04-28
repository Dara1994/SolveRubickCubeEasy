#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qgroupbox.h"
#include <QGroupBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGroupBox *gb=new QGroupBox(ui->groupBox);

}

MainWindow::~MainWindow()
{
    delete ui;
}
