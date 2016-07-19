#-------------------------------------------------
#
# Project created by QtCreator 2016-07-01T14:26:04
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lecteur
TEMPLATE = lib

CONFIG += debug_and_release
CONFIG(debug,debug|release) {
    DESTDIR = ../../../bin/debug
    OBJECTS_DIR = ../../../obj/lecteur/debug
    MOC_DIR = ../../../moc/lecteur/debug
    UI_DIR = ../../../ui/lecteur/debug
    LIBS += -L../../../bin/debug
    RCC_DIR += ../../../rcc/debug
} else {
    DESTDIR = ../../../bin/release
    OBJECTS_DIR = ../../../obj/lecteur/release
    MOC_DIR = ../../../moc/lecteur/release
    UI_DIR = ../../../ui/lecteur/release
    LIBS += -L../../../bin/release
    RCC_DIR += ../../../rcc/release
}


SOURCES +=\
    dialogcontroles.cpp \
    playermanager.cpp \
    mainwindowlecteur.cpp

HEADERS  += \
    dialogcontroles.h \
    playermanager.h \
    mainwindowlecteur.h

FORMS    += \
    dialogcontroles.ui \
    playermanager.ui \
    mainwindowlecteur.ui

DISTFILES +=

RESOURCES += \
    iconeslecteur.qrc

INCLUDEPATH += .
INCLUDEPATH += ../taglib
INCLUDEPATH += ../taglib/toolkit
INCLUDEPATH += ../taglib/mpeg
INCLUDEPATH += ../taglib/mpeg/id3v2


LIBS += -ltaglib
