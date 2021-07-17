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
        mainwidget.cpp \
    localmusic.cpp \
    downloadpage.cpp \
    cloudlist.cpp \
    likepage.cpp \
    login.cpp \
    playlist.cpp \
    lyricspage.cpp\
    readlyrics.cpp \
    listsingle.cpp \
    player.cpp \
    qmediainfo.cpp \
    httpGP.cpp \
    inifile.cpp \
    service.cpp \
    fileproce.cpp

HEADERS += \
        mainwidget.h \
    localmusic.h \
    downloadpage.h \
    cloudlist.h \
    likepage.h \
    login.h \
    playlist.h \
    lyricspage.h \
    readlyrics.h \
    listsingle.h \
    player.h \
    qmediainfo.h \
    httpGP.h \
    inifile.h \
    service.h \
    fileproce.h

FORMS += \
        mainwidget.ui \
    localmusic.ui \
    downloadpage.ui \
    cloudlist.ui \
    likepage.ui \
    login.ui \
    playlist.ui \
    lyricspage.ui \
    listsingle.ui

RESOURCES += \
    resourece.qrc
