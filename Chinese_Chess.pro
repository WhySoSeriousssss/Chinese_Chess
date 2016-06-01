#-------------------------------------------------
#
# Project created by QtCreator 2016-05-19T09:32:58
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chinese_Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CCoordinate.cpp \
    include/pugixml.cpp \
    util.cpp \
    CCoordinatesSet.cpp \
    QPiece.cpp \
    QBoard.cpp \
    QGameScene.cpp \
    CGame.cpp \
    CPiece.cpp \
    CPlayer.cpp

HEADERS  += mainwindow.h \
    Common.h \
    CCoordinate.h \
    include/pugiconfig.hpp \
    include/pugixml.hpp \
    util.h \
    CCoordinatesSet.h \
    QPiece.h \
    QBoard.h \
    IObserver.h \
    ISubject.h \
    QGameScene.h \
    CGame.h \
    CPiece.h \
    CPlayer.h

FORMS    += mainwindow.ui

DISTFILES +=
