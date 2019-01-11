#-------------------------------------------------
#
# Project created by QtCreator 2018-12-23T17:02:34
#
#-------------------------------------------------

QT       += core gui
RC_ICONS = src/images/icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mario
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    view.cpp \
    title.cpp \
    gamescene.cpp \
    backgrounditem.cpp \
    player.cpp \
    component.cpp \
    property.cpp \
    playerinfo.cpp \
    choosegames.cpp \
    tetris.cpp \
    snake.cpp \
    guessnum.cpp \
    guessgesture.cpp

HEADERS += \
        mainwindow.h \
    view.h \
    title.h \
    gamescene.h \
    backgrounditem.h \
    player.h \
    component.h \
    property.h \
    playerinfo.h \
    choosegames.h \
    tetris.h \
    snake.h \
    guessnum.h \
    guessgesture.h

FORMS += \
        mainwindow.ui \
    choosegames.ui \
    snakewidget.ui \
    guessnum.ui \
    guessnumnew.ui \
    guessgesture.ui \
    guessgesturenew.ui

RESOURCES += \
    src.qrc

DISTFILES +=
