#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T21:56:46
#
#-------------------------------------------------

QT       -= gui

TARGET = helpers
TEMPLATE = lib

DEFINES += HELPERS_LIBRARY

SOURCES += helpers.cpp

HEADERS += helpers.h\
        helpers_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
