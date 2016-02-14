#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T01:23:06
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpsocket.cpp \
    robot.cpp

HEADERS  += mainwindow.h \
    tcpsocket.h \
    globals.h \
    robot.h

FORMS    += mainwindow.ui
