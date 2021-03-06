#-------------------------------------------------
#
# Project created by QtCreator 2019-05-16T16:07:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diseno
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    abalonearbiter.cpp \
    abaloneboard.cpp \
        mainwindow.cpp \
    helpwindow.cpp \
    choosecolor.cpp \
    colors.cpp \
    abalone.cpp \
    piece.cpp \
    controller.cpp \
    abalonesaver.cpp \
    gameloader.cpp \
    abaloneloader.cpp \
    gamewindow.cpp \
    gameover.cpp \
    player.cpp

HEADERS += \
       mainwindow.h \
    helpwindow.h \
    choosecolor.h \
    colors.h \
    abalone.h \
    abaloneboard.h \
    board.h \
    game.h \
    piece.h \
    controller.h \
    saveable.h \
    saver.h \
    abalonesaver.h \
    loader.h \
    gameloader.h \
    abaloneloader.h \
    gamewindow.h \
    gameover.h \
    player.h \
    arbiter.h \
    abalonearbiter.h

FORMS += \
        mainwindow.ui \
    helpwindow.ui \
    choosecolor.ui \
    colors.ui \
    gamewindow.ui \
    gameover.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imagenes.qrc
win32:RC_FILE += abalone.rc
