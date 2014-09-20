#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T15:02:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FBX-Converter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    output.cpp \
    multiplefiles.cpp \
    about.cpp \
    help.cpp

HEADERS  += mainwindow.h \
    output.h \
    multiplefiles.h \
    about.h \
    help.h

FORMS    += mainwindow.ui \
    output.ui \
    multiplefiles.ui \
    about.ui \
    help.ui
