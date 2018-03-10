#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T21:43:28
#
#-------------------------------------------------

QT       += sql

QT       += gui

TARGET = bdd
TEMPLATE = lib

DEFINES += BDD_LIBRARY

LIBS += -lhelpers
LIBS += -ltaglib

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
INCLUDEPATH += ../taglib
INCLUDEPATH += ../taglib/toolkit
INCLUDEPATH += ../taglib/mpeg
INCLUDEPATH += ../taglib/mpeg/id3v2

SOURCES += bddsingleton.cpp \
    gestionverifications.cpp \
    changementversion.cpp \
    outilsbdd.cpp \
 bddartiste.cpp \
    bddalbum.cpp \
    bddrelation.cpp \
    bddmp3.cpp \
    bddpoch.cpp \
    bddphys.cpp \
    bddtype.cpp \
    bddtitre.cpp \
  bddconfig.cpp \
 bddstats.cpp \
   bddrech.cpp \
    bddsupport.cpp \
    idowner.cpp \
 meta_artiste.cpp \
    tags.cpp \
    meta_album.cpp \
    meta_titre.cpp


HEADERS += bdd_global.h \
    bddsingleton.h \
    gestionverifications.h \
    changementversion.h \
    outilsbdd.h \
tags.h \
 bddartiste.h \
bddalbum.h \
    bddrelation.h \
    bddmp3.h \
    bddpoch.h \
    bddphys.h \
    bddtype.h \
    bddtitre.h \
  bddconfig.h \
  bddstats.h \
 bddrech.h \
    bddsupport.h \
    meta_titre.h \
    meta_album.h \
idowner.h \
    meta_artiste.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
