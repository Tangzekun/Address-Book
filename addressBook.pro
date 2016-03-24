#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T00:08:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = addressBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    person.cpp

HEADERS  += mainwindow.h \
    person.h

FORMS    += mainwindow.ui
