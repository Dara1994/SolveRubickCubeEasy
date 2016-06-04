/********************************************************************************
** Form generated from reading UI file 'rubik.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUBIK_H
#define UI_RUBIK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *new_game_btn;
    QPushButton *make_cube_btn;
    QPushButton *solve_it_btn;
    QPushButton *I_give_up;
    QSpacerItem *horizontalSpacer;
    QGroupBox *rubick_group_box;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTextBrowser *Game_explained;
    QLabel *label;
    QPlainTextEdit *write_steps;
    QMenuBar *menuBar;
    QMenu *menuKockica;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(960, 700);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setSizeIncrement(QSize(100, 100));
        MainWindow->setBaseSize(QSize(600, 600));
        MainWindow->setAcceptDrops(false);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setStyleSheet(QLatin1String("QtMainWindow{\n"
"background-image:url(:/images/canvas3.jpg);}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        new_game_btn = new QPushButton(centralWidget);
        new_game_btn->setObjectName(QStringLiteral("new_game_btn"));
        new_game_btn->setStyleSheet(QLatin1String("QPushButton{\n"
"border-color: 10px solid red;\n"
"border	-radius: 10px;\n"
"font: 75 12pt \"Purisa\";\n"
"}"));

        verticalLayout_3->addWidget(new_game_btn);

        make_cube_btn = new QPushButton(centralWidget);
        make_cube_btn->setObjectName(QStringLiteral("make_cube_btn"));
        make_cube_btn->setStyleSheet(QStringLiteral("font: 75 12pt \"Purisa\";"));

        verticalLayout_3->addWidget(make_cube_btn);

        solve_it_btn = new QPushButton(centralWidget);
        solve_it_btn->setObjectName(QStringLiteral("solve_it_btn"));
        solve_it_btn->setStyleSheet(QStringLiteral("font: 75 12pt \"Purisa\";"));

        verticalLayout_3->addWidget(solve_it_btn);

        I_give_up = new QPushButton(centralWidget);
        I_give_up->setObjectName(QStringLiteral("I_give_up"));
        I_give_up->setStyleSheet(QStringLiteral("font: 75 12pt \"Purisa\";"));

        verticalLayout_3->addWidget(I_give_up);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        rubick_group_box = new QGroupBox(centralWidget);
        rubick_group_box->setObjectName(QStringLiteral("rubick_group_box"));
        rubick_group_box->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rubick_group_box->sizePolicy().hasHeightForWidth());
        rubick_group_box->setSizePolicy(sizePolicy1);
        rubick_group_box->setMinimumSize(QSize(200, 300));
        rubick_group_box->setStyleSheet(QLatin1String("QGroupBox {\n"
"background-color: rgb(181, 177, 177);\n"
"border: 5px solid black;\n"
"border-radius: 5px;\n"
"margin-top: 1ex; /* leave space at the top for the title */\n"
"}"));

        horizontalLayout->addWidget(rubick_group_box);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("font: 75 12pt \"Purisa\";"));

        verticalLayout_2->addWidget(label_2);

        Game_explained = new QTextBrowser(centralWidget);
        Game_explained->setObjectName(QStringLiteral("Game_explained"));
        Game_explained->setStyleSheet(QLatin1String("QTextBrowser {\n"
"background-color: rgb(255, 255, 255);\n"
" border: 2px solid gray;\n"
" border-radius: 5px;\n"
" margin-top: 1ex; /* leave space at the top for the title */\n"
"}"));

        verticalLayout_2->addWidget(Game_explained);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("font: 75 12pt \"Purisa\";"));

        verticalLayout_2->addWidget(label);

        write_steps = new QPlainTextEdit(centralWidget);
        write_steps->setObjectName(QStringLiteral("write_steps"));
        write_steps->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        verticalLayout_2->addWidget(write_steps);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 22));
        menuKockica = new QMenu(menuBar);
        menuKockica->setObjectName(QStringLiteral("menuKockica"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuKockica->menuAction());
        menuKockica->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(I_give_up, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        new_game_btn->setText(QApplication::translate("MainWindow", "New game!", 0));
        make_cube_btn->setText(QApplication::translate("MainWindow", "Make a cube!", 0));
        solve_it_btn->setText(QApplication::translate("MainWindow", "Solve it!", 0));
        I_give_up->setText(QApplication::translate("MainWindow", "I give up!", 0));
        rubick_group_box->setTitle(QString());
        label_2->setText(QApplication::translate("MainWindow", "Commands:", 0));
        Game_explained->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Rotate top of the cube: </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- right ( <span style=\" font-weight:600; color:#7c0f0f;\">TR</span> )          	 - left ( <span style=\" font-weight:600; color:#7c0f0f;\">TL </span>)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- press <span style=\" font-weight:600; font-style:italic;\">I                  	</span>- press <span style=\" font-weight:600; font-st"
                        "yle:italic; color:#7c0f0f;\">R</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Rotate left side of the cube:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">-upward ( <span style=\" font-weight:600; color:#7c0f0f;\">LU </span>)      	 - downward ( <span style=\" font-weight:600; color:#7c0f0f;\">LD</span> )</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- press <span style=\" font-weight:600; font-style:italic; color:#7c0f0f;\">K                 	 </span>- press <span style=\" font-weight:600; font-style:italic; color:#7c0f0f;\">J</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Rotate rigt side of the cube:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px;"
                        " margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- upward (<span style=\" font-weight:600; color:#7c0f0f;\">RU</span>)       	 - downward (<span style=\" font-weight:600; color:#7c0f0f;\">RD</span>)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- press <span style=\" font-weight:600; font-style:italic; color:#7c0f0f;\">D                	 </span>- press <span style=\" font-weight:600; font-style:italic; color:#7c0f0f;\">F</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Rotate bottom of the cube to the:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- right ( <span style=\" font-weight:600; color:#7c0f0f;\">DR</span> )          	 - left ( <span style=\" font-weight:600; color:#7c0f0f;\">DL </span>)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; ma"
                        "rgin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- press <span style=\" font-weight:600; font-style:italic; color:#7c0f0f;\">M               	 - </span>press <span style=\" font-weight:600; font-style:italic; color:#7c0f0f;\">C</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Rotate front of the cube to:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- right (<span style=\" font-weight:600; color:#7c0f0f;\">FR</span>)             	 - left (<span style=\" font-weight:600; color:#7c0f0f;\">FL</span>)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">- press <span style=\" font-weight:600; font-style:italic; color:#7c0f0f;\">H	          	 - </span>press <span style=\" font-weight:600; font-style:italic; color:#7c0f0f;\">G</span></p></body></html>", 0));
        label->setText(QApplication::translate("MainWindow", "Steps:", 0));
        menuKockica->setTitle(QApplication::translate("MainWindow", "Kockica", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUBIK_H
