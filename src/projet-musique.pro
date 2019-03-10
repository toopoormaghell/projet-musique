#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T11:24:05
#
#-------------------------------------------------

TEMPLATE = subdirs

SUBDIRS = \
    bdd \
    core \
    helpers \
    lecteur \
    qawswrapper \
    taglib

bdd.depends = helpers taglib
core.depends = bdd helpers lecteur qawswrapper taglib
qawswrapper.depends = bdd helpers
lecteur.depends = taglib

DISTFILES += style.astylerc
