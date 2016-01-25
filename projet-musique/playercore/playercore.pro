#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T21:37:53
#
#-------------------------------------------------

QT       -= gui
QT += multimedia

TARGET = playercore
TEMPLATE = lib

DEFINES += PLAYERCORE_LIBRARY

SOURCES += playercore.cpp

HEADERS += playercore.h\
        playercore_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
