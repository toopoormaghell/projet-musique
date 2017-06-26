QT       += core gui sql network multimedia

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

LIBS += -ltaglib
LIBS += -lqawswrapper
LIBS += -llecteur


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
    dialogconfigactu.h \
    bddconfig.h \
    ongletstats.h \
    bddstats.h \
    ongletrech.h \
    bddrech.h \
    dialogchoixpochette.h \
    DialogAjouterPhys.h \
    bddlecteur.h \
    ongletfusion.h \
    MyQLabel.h \
    bddfusion.h \
    tags.h \
    dialogchoixtitrefusion.h \
    DialogChoixAlbumPhys.h \
    DialogModifierArtiste.h \
    DialogModifierAlbum.h \
    DialogVidageBDD.h \
    DialogAjoutTitre.h \
    bddsupport.h \
    idowner.h \
    bddversion5.h \
    bddversion6.h \
    dialogverifications.h \
    gestionverifications.h


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
    dialogconfigactu.cpp \
    bddconfig.cpp \
    ongletstats.cpp \
    bddstats.cpp \
    ongletrech.cpp \
    bddrech.cpp \
    dialogchoixpochette.cpp \
    DialogAjouterPhys.cpp \
    bddlecteur.cpp \
    ongletfusion.cpp \
    MyQLabel.cpp \
    bddfusion.cpp \
    tags.cpp \
    dialogchoixtitrefusion.cpp \
    DialogChoixAlbumPhys.cpp \
    DialogModifierArtiste.cpp \
    DialogModifierAlbum.cpp \
    DialogVidageBDD.cpp \
    DialogAjoutTitre.cpp \
    bddsupport.cpp \
    idowner.cpp \
    bddversion5.cpp \
    bddversion6.cpp \
    dialogverifications.cpp \
    gestionverifications.cpp

FORMS += \
    ongletmp3.ui \
    ongletphys.ui \
    mainwindow.ui \
    dialogconfigactu.ui \
    ongletstats.ui \
    ongletrech.ui \
    dialogchoixpochette.ui \
    DialogAjouterPhys.ui \
    ongletfusion.ui \
    dialogchoixtitrefusion.ui \
    DialogChoixAlbumPhys.ui \
    DialogModifierArtiste.ui \
    DialogModifierAlbum.ui \
    DialogVidageBDD.ui \
    DialogAjoutTitre.ui \
    dialogverifications.ui


OTHER_FILES += \
    projet_musique.cppcheck \
    uml-diagram.uxf

RESOURCES += \
    IconesMenu.qrc



