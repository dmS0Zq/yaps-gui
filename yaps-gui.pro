#-------------------------------------------------
#
# Project created by QtCreator 2014-10-22T23:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = yaps-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Database.cpp \
    DateTime.cpp \
    Entry.cpp \
    FileIO.cpp \
    entrydisplaywindow.cpp \
    fulltreewidget.cpp \
    PasswordPolicy.cpp

HEADERS  += mainwindow.h \
    Database.h \
    DateTime.h \
    Entry.h \
    FileIO.h \
    LinkedListNode.h \
    Tree.h \
    entrydisplaywindow.h \
    fulltreewidget.h \
    PasswordPolicy.h

CONFIG += \
    c++11

FORMS    += mainwindow.ui \
    entrydisplaywindow.ui \
    fulltreewidget.ui

OTHER_FILES += \
    deployment.pri \
    FileFormat.txt
