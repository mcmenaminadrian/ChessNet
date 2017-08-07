#-------------------------------------------------
#
# Project created by QtCreator 2017-08-04T12:46:13
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessNet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chessnet.cpp \
    chessinput.cpp \
    filternet.cpp \
    leveloneneuron.cpp \
    fullyconnected.cpp

HEADERS  += mainwindow.hpp \
    chessnet.hpp \
    chessinput.hpp \
    filternet.hpp \
    leveloneneuron.hpp \
    fullyconnected.hpp \
    activation.hpp

FORMS    += mainwindow.ui
