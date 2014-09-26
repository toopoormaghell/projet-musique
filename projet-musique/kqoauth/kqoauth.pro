#-------------------------------------------------
#
# Project created by QtCreator 2014-09-25T21:54:40
#
#-------------------------------------------------

QT       -= gui
QT       += network

TARGET = kqoauth
TEMPLATE = lib

CONFIG += debug_and_release
CONFIG(debug,debug|release) {
    DESTDIR = ../../../bin/debug
    OBJECTS_DIR = ../../../obj/kqoauth/debug
    MOC_DIR = ../../../moc/kqoauth/debug
    UI_DIR = ../../../ui/kqoauth/debug
} else {
    DESTDIR = ../../../bin/release
    OBJECTS_DIR = ../../../obj/kqoauth/release
    MOC_DIR = ../../../moc/kqoauth/release
    UI_DIR = ../../../ui/kqoauth/release
}

DEFINES += KQOAUTH

SOURCES += \
    kqoauthauthreplyserver.cpp \
    kqoauthmanager.cpp \
    kqoauthrequest.cpp \
    kqoauthrequest_1.cpp \
    kqoauthrequest_xauth.cpp \
    kqoauthutils.cpp

HEADERS += \
    kqoauthauthreplyserver.h \
    kqoauthauthreplyserver_p.h \
    kqoauthglobals.h \
    kqoauthmanager.h \
    kqoauthmanager_p.h \
    kqoauthrequest.h \
    kqoauthrequest_1.h \
    kqoauthrequest_p.h \
    kqoauthrequest_xauth.h \
    kqoauthrequest_xauth_p.h \
    kqoauthutils.h
