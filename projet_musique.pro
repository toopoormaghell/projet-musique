#-------------------------------------------------
#
# Project created by QtCreator 2014-01-15T13:08:45
#
#-------------------------------------------------

QT       += core gui sql network xml
QT       += phonon
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# include(../projet-musique/kqoauth/kqoauth.prl)

TARGET = projet_musique
TEMPLATE = app

CONFIG += kqoauth

INCLUDEPATH += ./taglib/inc
INCLUDEPATH += ./taglib/inc/toolkit
INCLUDEPATH += ./taglib/inc/mpeg/id3v2/
INCLUDEPATH += ./taglib/inc/mpeg/
INCLUDEPATH += ./taglib/inc/mpeg/id3v2/frames
INCLUDEPATH += ./kqoauth/src/
LIBS += -L../projet-musique/kqoauth/lib -lkqoauthd0
LIBS += -ltaglib -L../projet-musique/taglib/lib


message($$LIBS)

#Defines for TagLib :
DEFINES += HAVE_ZLIB=0 NDEBUG WITH_ASF WITH_MP4 TAGLIB_WITH_ASF TAGLIB_WITH_MP4 TAGLIB_NO_CONFIG MAKE_TAGLIB_LIB

SOURCES += main.cpp\
        fenetreprincipale.cpp \
    ongletmp3.cpp \
    ongletphys.cpp \
    ongletplaylist.cpp \
    bddinterface.cpp \
    bddcommun.cpp \
    bddphys.cpp \
    bddmp3.cpp \
    util.cpp \
    bddsingleton.cpp \
    barreavancement.cpp \
    importationlistephysiques.cpp \
    discogs.cpp \
    dialogueajouterphysique.cpp \
    affichagecommun.cpp \
    dialogueartistesinverses.cpp \
    player.cpp \
    autorisationdiscogs.cpp \
    kqoauthsingleton.cpp \
    saisietokensapi.cpp \
    apimusicpro.cpp \
    oauthrequestfinisher.cpp

HEADERS  += fenetreprincipale.h \
    ongletmp3.h \
    ongletphys.h \
    ongletplaylist.h \
    bddinterface.h \
    bddcommun.h \
    bddphys.h \
    bddmp3.h \
    util.h \
    bddsingleton.h \
    barreavancement.h \
    importationlistephysiques.h \
    discogs.h \
    dialogueajouterphysique.h \
    affichagecommun.h \
    dialogueartistesinverses.h \
    player.h \
    autorisationdiscogs.h \
    kqoauthsingleton.h \
    saisietokensapi.h \
    apimusicpro.h \
    oauthrequestfinisher.h

FORMS    += fenetreprincipale.ui \
    ongletmp3.ui \
    ongletphys.ui \
    ongletplaylist.ui \
    barreavancement.ui \
    importationlistephysiques.ui \
    dialogueajouterphysique.ui \
    dialogueartistesinverses.ui \
    player.ui \
    saisietokensapi.ui
