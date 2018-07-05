#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T11:10:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#DEFINES += QT_MESSAGELOGCONTEXT #//release
#DEFINES+=QT_NO_DEBUG_OUTPUT

TARGET = Net_Analysis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qmymdisubwindow.cpp \
    phoneticwidgetform.cpp \
    setui.cpp \
    cwidget.cpp \
    aboutdialog.cpp \
    descdialog.cpp

HEADERS  += mainwindow.h \
    qmymdisubwindow.h \
    phoneticwidgetform.h \
    global.h \
    setui.h \
    cwidget.h \
    aboutdialog.h \
    descdialog.h

FORMS    += mainwindow.ui \
    phoneticwidgetform.ui \
    setui.ui \
    aboutdialog.ui \
    descdialog.ui




unix|win32: LIBS += -LE:/nowWork/Voice_Engine_Tools/Net_Read/Net_Read_Dir/Net_Read_Dir/lib -lAsecMN

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

RESOURCES += \
    file.qrc

DISTFILES +=






