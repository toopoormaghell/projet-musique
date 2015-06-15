QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = core
TEMPLATE = app

CONFIG += debug_and_release
CONFIG(debug,debug|release) {
    DESTDIR = ../../../bin/debug
    OBJECTS_DIR = ../../../obj/core/debug
    MOC_DIR = ../../../moc/core/debug
    UI_DIR = ../../../ui/core/debug
    LIBS += -L../../../bin/debug
} else {
    DESTDIR = ../../../bin/release
    OBJECTS_DIR = ../../../obj/core/release
    MOC_DIR = ../../../moc/core/release
    UI_DIR = ../../../ui/core/release
    LIBS += -L../../../bin/release
}

INCLUDEPATH += .
INCLUDEPATH += ../taglib
INCLUDEPATH += ../taglib/toolkit
INCLUDEPATH += ../taglib/mpeg
INCLUDEPATH += ../taglib/mpeg/id3v2
INCLUDEPATH += ../kqoauth
LIBS += -lkqoauth
LIBS += -ltaglib

HEADERS += \
    bddsingleton.h \
    bddartiste.h \
    ongletmp3.h \
    ongletphys.h \
    bddalbum.h \
    bddrelation.h \
    bddmp3.h \
    bddpoch.h \
    bddphys.h \
    bddaffichermp3.h \
    bddafficherphys.h \
    bddgestionmp3.h \
    bddgestionphys.h \
    util.h \
    mainwindow.h \
    bddtype.h \
    bddtitre.h \
    dialogajouterphys.h \
    rechercheurl.h \
    kqoauthsingleton.h \
    dialogconfigactu.h \
    bddconfig.h \
    sousdialogajouttitre.h


SOURCES += main.cpp \
    bddsingleton.cpp \
    bddartiste.cpp \
    ongletmp3.cpp \
    ongletphys.cpp \
    bddalbum.cpp \
    bddrelation.cpp \
    bddmp3.cpp \
    bddpoch.cpp \
    bddphys.cpp \
    bddaffichermp3.cpp \
    bddafficherphys.cpp \
    bddgestionmp3.cpp \
    bddgestionphys.cpp \
    util.cpp \
    mainwindow.cpp \
    bddtype.cpp \
    bddtitre.cpp \
    dialogajouterphys.cpp \
    rechercheurl.cpp \
    kqoauthsingleton.cpp \
    dialogconfigactu.cpp \
    bddconfig.cpp \
    sousdialogajouttitre.cpp

FORMS += \
    ongletmp3.ui \
    ongletphys.ui \
    mainwindow.ui \
    dialogajouterphys.ui \
    dialogconfigactu.ui \
    sousdialogajouttitre.ui


OTHER_FILES += \
    projet_musique.cppcheck \
    ../../../bin/release/default.qss \
    uml-diagram.uxf \
    ../../../moc/core/correct-icone-8516-128.png \
    ../../../bin/release/mp3phys.png \
    ../../../bin/release/nonmp3phys.png

RESOURCES += \
    IconesMenu.qrc


