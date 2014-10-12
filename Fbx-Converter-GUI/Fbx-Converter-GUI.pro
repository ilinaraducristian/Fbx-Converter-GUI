#-------------------------------------------------
#
# Project created by QtCreator 2014-09-30T22:35:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fbx-Converter-GUI
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    processingdialog.cpp \
    output.cpp \
    help.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    processingdialog.h \
    output.h \
    help.h \
    about.h

FORMS    += mainwindow.ui \
    processingdialog.ui \
    output.ui \
    help.ui \
    about.ui
CONFIG += c++11

RESOURCES +=

OTHER_FILES +=
