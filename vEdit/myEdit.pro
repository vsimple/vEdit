#-------------------------------------------------
#
# Project created by QtCreator 2015-07-24T10:50:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myEdit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    taba.cpp \
    tabb.cpp \
    codeeditor.cpp \
    highlighter.cpp \
    windowtofind.cpp \
    windowtoreplace.cpp

HEADERS  += mainwindow.h \
    taba.h \
    tabb.h \
    codeeditor.h \
    highlighter.h \
    windowtofind.h \
    windowtoreplace.h

FORMS    += mainwindow.ui \
    windowtofind.ui \
    windowtoreplace.ui

RESOURCES += \
    res.qrc

DISTFILES +=
