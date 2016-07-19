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
    LIBS += -L../../../bin/debug
} else {
    LIBS += -L../../../bin/release
  }

SOURCES += main.cpp\
    dialogcontroles.cpp \
    mainwindow.cpp \
    playermanager.cpp

HEADERS  += \
    dialogcontroles.h \
    mainwindow.h \
    playermanager.h

FORMS    += \
    dialogcontroles.ui \
    mainwindow.ui \
    playermanager.ui

DISTFILES +=

RESOURCES += \
    iconeslecteur.qrc

INCLUDEPATH += .
INCLUDEPATH += ../taglib
INCLUDEPATH += ../taglib/toolkit
INCLUDEPATH += ../taglib/mpeg
INCLUDEPATH += ../taglib/mpeg/id3v2


LIBS += -ltaglib
