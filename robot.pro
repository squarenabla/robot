#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T01:23:06
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = robot
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    tcpsocket.cpp \
    robot.cpp \
    pidregulator.cpp \
    painter.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    tcpsocket.h \
    globals.h \
    robot.h \
    pidregulator.h \
    painter.h \
    qcustomplot.h

FORMS    += mainwindow.ui
