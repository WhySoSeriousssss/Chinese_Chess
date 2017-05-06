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
    include/pugixml.cpp \
    util.cpp \
    model/CCoordinate.cpp \
    model/CCoordinatesSet.cpp \
    model/CGame.cpp \
    model/CPiece.cpp \
    model/CPlayer.cpp \
    model/CMovement.cpp \
    model/CActionStack.cpp \
    view-controller/QPiece.cpp \
    view-controller/QBoard.cpp \
    view-controller/QGameScene.cpp \

HEADERS  += mainwindow.h \
    Common.h \
    include/pugiconfig.hpp \
    include/pugixml.hpp \
    util.h \
    IObserver.h \
    ISubject.h \
    model/CCoordinate.h \
    model/CCoordinatesSet.h \
    model/CGame.h \
    model/CPiece.h \
    model/CPlayer.h \
    model/CMovement.h \
    model/CActionStack.h \
    view-controller/QPiece.h \
    view-controller/QBoard.h \
    view-controller/QGameScene.h \

FORMS    += mainwindow.ui

DISTFILES +=
