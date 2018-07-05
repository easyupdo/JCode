#-------------------------------------------------
#
# Project created by QtCreator 2018-03-27T11:14:39
#
#-------------------------------------------------

QT       += core gui
QT       +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Protocol_Only
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    protocolmessage.cpp \
    protocol_debug.cpp \
    md5.cpp \
    net_set.cpp

HEADERS  += mainwindow.h \
    protocolmessage.h \
    protocol_debug.h \
    md5.h \
    net_set.h

FORMS    += mainwindow.ui \
    protocol_debug.ui \
    net_set.ui
