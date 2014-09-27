QT       += core gui sql network xml
QT       += phonon

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

FORMS += \
    barreavancement.ui \
    dialogajouterplaylistmp3.ui \
    dialogajoutplaylist.ui \
    dialogchangerpochette.ui \
    dialogdossierpardef.ui \
    dialogmodifieralbum.ui \
    dialogueajouterphysique.ui \
    dialogueartistesinverses.ui \
    dialogvidermp3.ui \
    fenetreprincipale.ui \
    importationlistephysiques.ui \
    ongletmp3.ui \
    ongletphys.ui \
    ongletplaylist.ui \
    player.ui \
    saisietokensapi.ui

OTHER_FILES += \
    projet_musique.cppcheck

HEADERS += \
    affichagecommun.h \
    barreavancement.h \
    BDDcommun.h \
    bddinterface.h \
    bddmp3.h \
    bddphys.h \
    bddplaylist.h \
    bddsingleton.h \
    dialogajouterplaylistmp3.h \
    dialogajoutplaylist.h \
    dialogchangerpochette.h \
    dialogdossierpardef.h \
    dialogmodifieralbum.h \
    dialogueajouterphysique.h \
    dialogueartistesinverses.h \
    dialogvidermp3.h \
    discogs.h \
    fenetreprincipale.h \
    importationlistephysiques.h \
    kqoauthsingleton.h \
    oauthrequestfinisher.h \
    ongletmp3.h \
    ongletphys.h \
    ongletplaylist.h \
    player.h \
    saisietokensapi.h \
    util.h

SOURCES += \
    affichagecommun.cpp \
    barreavancement.cpp \
    bddcommun.cpp \
    bddinterface.cpp \
    bddmp3.cpp \
    bddphys.cpp \
    bddplaylist.cpp \
    bddsingleton.cpp \
    dialogajouterplaylistmp3.cpp \
    dialogajoutplaylist.cpp \
    dialogchangerpochette.cpp \
    dialogdossierpardef.cpp \
    dialogmodifieralbum.cpp \
    dialogueajouterphysique.cpp \
    dialogueartistesinverses.cpp \
    dialogvidermp3.cpp \
    discogs.cpp \
    fenetreprincipale.cpp \
    importationlistephysiques.cpp \
    kqoauthsingleton.cpp \
    main.cpp \
    oauthrequestfinisher.cpp \
    ongletmp3.cpp \
    ongletphys.cpp \
    ongletplaylist.cpp \
    player.cpp \
    saisietokensapi.cpp \
    util.cpp