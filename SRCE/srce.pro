#-------------------------------------------------
#
# Project created by QtCreator 2012-11-24T13:22:32
#
#-------------------------------------------------
QT += widgets
QT       += core gui opengl

LIBS	+= -lGLU
TARGET = srce
TEMPLATE = app


SOURCES += main.cpp\
        rubik.cpp \
    mainwindow.cpp

HEADERS  += rubik.h \
    mainwindow.h

FORMS    += rubik.ui
