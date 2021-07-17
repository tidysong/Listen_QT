#-------------------------------------------------
#
# Project created by QtCreator 2021-07-09T23:11:49
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = listen
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    cloudlist.cpp \
    downloadpage.cpp \
    fileproce.cpp \
    httpGP.cpp \
    inifile.cpp \
    likepage.cpp \
    listsingle.cpp \
    loading.cpp \
    localmusic.cpp \
    login.cpp \
    lyricspage.cpp \
    mainwidget.cpp \
    mydialog.cpp \
    player.cpp \
    playlist.cpp \
    qmediainfo.cpp \
    readlyrics.cpp \
    searchinfo.cpp \
    searchonline.cpp \
    service.cpp \
    sigup.cpp

HEADERS += \
    cloudlist.h \
    downloadpage.h \
    fileproce.h \
    httpGP.h \
    inifile.h \
    likepage.h \
    listsingle.h \
    loading.h \
    localmusic.h \
    login.h \
    lyricspage.h \
    mainwidget.h \
    mydialog.h \
    player.h \
    playlist.h \
    qmediainfo.h \
    readlyrics.h \
    searchinfo.h \
    searchonline.h \
    service.h \
    sigup.h


FORMS += \
    cloudlist.ui \
    downloadpage.ui \
    likepage.ui \
    listsingle.ui \
    loading.ui \
    localmusic.ui \
    login.ui \
    lyricspage.ui \
    mainwidget.ui \
    mydialog.ui \
    playlist.ui \
    searchonline.ui \
    sigup.ui

RESOURCES += \
    resourece.qrc
