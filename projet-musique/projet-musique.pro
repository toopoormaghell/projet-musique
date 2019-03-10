#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T11:24:05
#
#-------------------------------------------------

TEMPLATE = subdirs

SUBDIRS = \
    Bdd \
    core \
    helpers \
    Lecteur \
    QAWSWrapper \
    taglib

Bdd.depends = helpers taglib
core.depends = Bdd helpers Lecteur QAWSWrapper taglib
QAWSWrapper.depends = Bdd helpers
Lecteur.depends = taglib

DISTFILES += style.astylerc
