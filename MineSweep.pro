#-------------------------------------------------
#
# Project created by QtCreator 2015-12-14T00:07:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MineMap.cpp

HEADERS  += mainwindow.h \
    MineMap.h

FORMS    += mainwindow.ui

RESOURCES += \
    hellores.qrc

DISTFILES += \
    README.md
