#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T11:04:27
#
#-------------------------------------------------

#QT       += core gui
QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WApp
TEMPLATE = app

LIBS	+= -lGLU
SOURCES += main.cpp\
        mainwindow.cpp \
    rubik.cpp \
    pokreti.cpp \
    cube.cpp

HEADERS  += mainwindow.h \
    rubik.h \
    pokreti.h \
    cube.h

FORMS    += \
    rubik.ui
