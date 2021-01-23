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
    bddgestionmodifnomartiste.h \
    bddlisteplaylist.h \
    bddrel_playlist.h \
    dialogajoutenplaylist.h \
    dialogajoutpoch.h \
    dialogmodifnomsartistes.h \
      ongletmp3.h \
    ongletphys.h \
       bddaffichermp3.h \
    bddafficherphys.h \
    bddgestionmp3.h \
    bddgestionphys.h \
    mainwindow.h \
    dialogconfigactu.h \
    ongletplaylist.h \
    ongletproblemes.h \
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
    bddafficherliste.h \
    ongleterreurs.h


SOURCES += main.cpp \
    bddgestionmodifnomartiste.cpp \
    bddlisteplaylist.cpp \
    bddrel_playlist.cpp \
    dialogajoutenplaylist.cpp \
    dialogajoutpoch.cpp \
    dialogmodifnomsartistes.cpp \
    ongletmp3.cpp \
    ongletphys.cpp \
    bddaffichermp3.cpp \
    bddafficherphys.cpp \
    bddgestionmp3.cpp \
    bddgestionphys.cpp \
    mainwindow.cpp \
    dialogconfigactu.cpp \
    ongletplaylist.cpp \
    ongletproblemes.cpp \
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
    bddafficherliste.cpp \
    ongleterreurs.cpp


FORMS += \
    dialogajoutenplaylist.ui \
    dialogajoutpoch.ui \
    dialogmodifnomsartistes.ui \
    ongletmp3.ui \
    ongletphys.ui \
    mainwindow.ui \
    dialogconfigactu.ui \
    ongletplaylist.ui \
    ongletproblemes.ui \
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
    ongleterreurs.ui


OTHER_FILES += \
    projet_musique.cppcheck \
    uml-diagram.uxf

RESOURCES += \
    IconesMenu.qrc



