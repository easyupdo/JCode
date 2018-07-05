#-------------------------------------------------
#
# Project created by QtCreator 2017-08-08T13:55:24
#
#-------------------------------------------------

QT       += core gui
QT       +=network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = voice_record
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    md5.cpp \
    hmi.cpp

HEADERS  += mainwindow.h \
    md5.h \
    hmi.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

DISTFILES +=
