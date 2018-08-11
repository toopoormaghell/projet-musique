QT       += core gui sql network multimedia
win32:QT += winextras

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
    RCC_DIR += ../../../rcc/debug
} else {
    DESTDIR = ../../../bin/release
    OBJECTS_DIR = ../../../obj/core/release
    MOC_DIR = ../../../moc/core/release
    UI_DIR = ../../../ui/core/release
    LIBS += -L../../../bin/release
    RCC_DIR += ../../../rcc/release
}

INCLUDEPATH += .
INCLUDEPATH += ../taglib
INCLUDEPATH += ../taglib/toolkit
INCLUDEPATH += ../taglib/mpeg
INCLUDEPATH += ../taglib/mpeg/id3v2
INCLUDEPATH += ../qawswrapper
INCLUDEPATH += ../lecteur
INCLUDEPATH += ../helpers
INCLUDEPATH += ../bdd

LIBS += -ltaglib
LIBS += -lqawswrapper
LIBS += -llecteur
LIBS += -lhelpers
LIBS += -lbdd


HEADERS += \
      ongletmp3.h \
    ongletphys.h \
       bddaffichermp3.h \
    bddafficherphys.h \
    bddgestionmp3.h \
    bddgestionphys.h \
    mainwindow.h \
    dialogconfigactu.h \
      ongletstats.h \
     ongletrech.h \
       dialogchoixpochette.h \
    DialogAjouterPhys.h \
    bddlecteur.h \
    DialogModifierArtiste.h \
    DialogModifierAlbum.h \
    DialogVidageBDD.h \
    DialogAjoutTitre.h \
      dialogverifications.h \
       ongletartiste.h \
    bddafficherartiste.h \
    dialogalbumssmp3.h \
    ongletliste.h \
    bddafficherliste.h \
    mp3remover.h \
    ongleterreurs.h


SOURCES += main.cpp \
    ongletmp3.cpp \
    ongletphys.cpp \
    bddaffichermp3.cpp \
    bddafficherphys.cpp \
    bddgestionmp3.cpp \
    bddgestionphys.cpp \
    mainwindow.cpp \
    dialogconfigactu.cpp \
    ongletstats.cpp \
    ongletrech.cpp \
    dialogchoixpochette.cpp \
    DialogAjouterPhys.cpp \
    bddlecteur.cpp \
    DialogModifierArtiste.cpp \
    DialogModifierAlbum.cpp \
    DialogVidageBDD.cpp \
    DialogAjoutTitre.cpp \
    dialogverifications.cpp \
    ongletartiste.cpp \
    bddafficherartiste.cpp \
    dialogalbumssmp3.cpp \
    ongletliste.cpp \
    bddafficherliste.cpp \
    mp3remover.cpp \
    ongleterreurs.cpp


FORMS += \
    ongletmp3.ui \
    ongletphys.ui \
    mainwindow.ui \
    dialogconfigactu.ui \
    ongletstats.ui \
    ongletrech.ui \
    dialogchoixpochette.ui \
    DialogAjouterPhys.ui \
    DialogChoixAlbumPhys.ui \
    DialogModifierArtiste.ui \
    DialogModifierAlbum.ui \
    DialogVidageBDD.ui \
    DialogAjoutTitre.ui \
    dialogverifications.ui \
    ongletartiste.ui \
    dialogalbumssmp3.ui \
    ongletliste.ui \
    ongleterreurs.ui


OTHER_FILES += \
    projet_musique.cppcheck \
    uml-diagram.uxf

RESOURCES += \
    IconesMenu.qrc



