#-------------------------------------------------
#
# Project created by QtCreator 2014-09-12T17:02:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FBX-Converter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cmdoutput.cpp \
    about.cpp \
    help.cpp \
    multiplefiles.cpp

HEADERS  += mainwindow.h \
    cmdoutput.h \
    about.h \
    help.h \
    multiplefiles.h

FORMS    += mainwindow.ui \
    cmdoutput.ui \
    about.ui \
    help.ui \
    multiplefiles.ui
