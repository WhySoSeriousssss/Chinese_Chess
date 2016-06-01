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
    CPiece_Model.cpp \
    CBoard_Model.cpp \
    CGame_Model.cpp \
    CPlayer_Model.cpp \
    CCoordinate.cpp \
    include/pugixml.cpp \
    util.cpp \
    CCoordinatesSet.cpp \
    QPiece.cpp \
    QBoard.cpp \
    QGameScene.cpp

HEADERS  += mainwindow.h \
    Common.h \
    CBoard_Model.h \
    CPiece_Model.h \
    CPlayer_Model.h \
    CGame_Model.h \
    CCoordinate.h \
    include/pugiconfig.hpp \
    include/pugixml.hpp \
    util.h \
    CCoordinatesSet.h \
    QPiece.h \
    QBoard.h \
    IObserver.h \
    ISubject.h \
    QGameScene.h

FORMS    += mainwindow.ui

DISTFILES +=
