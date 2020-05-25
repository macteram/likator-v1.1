#-------------------------------------------------
#
# Project created by QtCreator 2020-05-23T13:56:50
#
#-------------------------------------------------

QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = likator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    humaninfo.cpp

HEADERS  += mainwindow.h \
    humaninfo.h

FORMS    += mainwindow.ui \
    humaninfo.ui
