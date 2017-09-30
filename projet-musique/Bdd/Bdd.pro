#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T21:43:28
#
#-------------------------------------------------

QT       += sql

QT       += gui

TARGET = Bdd
TEMPLATE = lib

DEFINES += BDD_LIBRARY

LIBS += -lhelpers

CONFIG += debug_and_release
CONFIG(debug,debug|release) {
    DESTDIR = ../../../bin/debug
    OBJECTS_DIR = ../../../obj/bdd/debug
    MOC_DIR = ../../../moc/bdd/debug
    UI_DIR = ../../../ui/bdd/debug
    LIBS += -L../../../bin/debug
    RCC_DIR += ../../../rcc/debug
} else {
    DESTDIR = ../../../bin/release
    OBJECTS_DIR = ../../../obj/bdd/release
    MOC_DIR = ../../../moc/bdd/release
    UI_DIR = ../../../ui/bdd/release
    LIBS += -L../../../bin/release
    RCC_DIR += ../../../rcc/release
}

INCLUDEPATH += ../helpers

SOURCES += bddsingleton.cpp \
    gestionverifications.cpp \
    changementversion.cpp \
    outilsbdd.cpp

HEADERS += bdd_global.h \
    bddsingleton.h \
    gestionverifications.h \
    changementversion.h \
    outilsbdd.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
