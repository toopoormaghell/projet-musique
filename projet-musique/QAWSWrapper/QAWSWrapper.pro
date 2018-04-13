#-------------------------------------------------
#
# Project created by QtCreator 2016-01-25T22:34:45
#
#-------------------------------------------------

QT       += network
QT       += gui

TARGET = QAWSWrapper
TEMPLATE = lib

LIBS += -lhelpers
LIBS += -lbdd

CONFIG += debug_and_release
CONFIG(debug,debug|release) {
    DESTDIR = ../../../bin/debug
    OBJECTS_DIR = ../../../obj/QAWSWrapper/debug
    MOC_DIR = ../../../moc/QAWSWrapper/debug
    UI_DIR = ../../../ui/QAWSWrapper/debug
    LIBS += -L../../../bin/debug
    RCC_DIR += ../../../rcc/debug
} else {
    DESTDIR = ../../../bin/release
    OBJECTS_DIR = ../../../obj/QAWSWrapper/release
    MOC_DIR = ../../../moc/QAWSWrapper/release
    UI_DIR = ../../../ui/QAWSWrapper/release
    LIBS += -L../../../bin/release
    RCC_DIR += ../../../rcc/release
}

INCLUDEPATH += ../helpers \
               ../bdd

DEFINES += QAWSWRAPPER_LIBRARY

SOURCES += QAWSWrapper.cpp \
    QAWSWrapperNotifier.cpp

HEADERS += QAWSWrapper.h \
    QAWSWrapper_global.h \
    QAWSGlobalInfo.h \
    QAWSWrapperNotifier.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
