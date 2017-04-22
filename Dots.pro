#-------------------------------------------------
#
# Project created by QtCreator 2017-04-03T10:27:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Dots
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    dot.cpp \
    gamefield.cpp \
    refferee.cpp

HEADERS  += mainwindow.h \
    player.h \
    dot.h \
    gamefield.h \
    GeneralHeader.h \
    refferee.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc
