#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T21:43:28
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = Bdd
TEMPLATE = lib

DEFINES += BDD_LIBRARY

SOURCES += bdd.cpp

HEADERS += bdd.h\
        bdd_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
