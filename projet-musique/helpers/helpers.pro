#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T21:56:46
#
#-------------------------------------------------

QT       += gui

TARGET = helpers
TEMPLATE = lib

DEFINES += HELPERS_LIBRARY

CONFIG += debug_and_release
CONFIG(debug,debug|release) {
    DESTDIR =     ../../../bin/debug
    OBJECTS_DIR = ../../../obj/helpers/debug
    MOC_DIR =     ../../../moc/helpers/debug
    UI_DIR =      ../../../ui/helpers/debug
    LIBS +=     -L../../../bin/debug
    RCC_DIR +=    ../../../rcc/debug
} else {
    DESTDIR = ../../../bin/release
    OBJECTS_DIR = ../../../obj/helpers/release
    MOC_DIR = ../../../moc/helpers/release
    UI_DIR = ../../../ui/helpers/release
    LIBS += -L../../../bin/release
    RCC_DIR += ../../../rcc/release
}

SOURCES += util.cpp \
    handable.cpp

HEADERS += helpers_global.h \
    util.h \
    handable.h \
    handle.h \
    handle_impl.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
