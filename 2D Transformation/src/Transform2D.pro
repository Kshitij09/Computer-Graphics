#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T02:44:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Transform2D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clickablelabel.cpp \
    transmatrix.cpp

HEADERS  += mainwindow.h \
    clickablelabel.h \
    transmatrix.h

FORMS    += mainwindow.ui
