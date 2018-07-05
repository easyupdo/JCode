#-------------------------------------------------
#
# Project created by QtCreator 2017-06-16T14:47:58
#
#-------------------------------------------------

QT       += core gui
QT       +=sql
QT       +=network
QT       += multimedia
DEFINES += QT_MESSAGELOGCONTEXT #//release
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LSX_Management_System
TEMPLATE = app


SOURCES += \
    app/adpcm2pcm.cpp \
    app/company_about.cpp \
    app/delegateaddiconforsqlqyery.cpp \
    app/global.cpp \
    app/groupwork.cpp \
    app/imessagebox.cpp \
    app/mysqlsupport.cpp \
    app/pcm2play.cpp \
    app/protocolmessage.cpp \
    app/qmsqlquerymodel.cpp \
    app/qmtableviewdelegate.cpp \
    app/readypollinglistwork.cpp \
    app/rockwell.cpp \
    adddevicedialog.cpp \
    addduan_dialog.cpp \
    addoralterjiandialog.cpp \
    addpollingform.cpp \
    addquoralterdialog.cpp \
    addstationoralterdialog.cpp \
    adduserform.cpp \
    alterdevicedialog.cpp \
    alterpollingform.cpp \
    alteruserform.cpp \
    deluserdialog.cpp \
    devicecontrolform.cpp \
    deviceinfodialog.cpp \
    devicemanagementform.cpp \
    devicepollingform.cpp \
    dialog.cpp \
    doublecleckedform.cpp \
    duanalterdialog.cpp \
    duandialog.cpp \
    faultsearchdialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    realtimedevicecontrolform.cpp \
    realtimemonitoring.cpp \
    sysmanagementform.cpp \
    troublelogform.cpp \
    userinfoform.cpp \
    userlogform.cpp \
    realtimework.cpp \
    app/md5.cpp
HEADERS  += \
    app/adpcm2pcm.h \
    app/company_about.h \
    app/delegateaddiconforsqlqyery.h \
    app/global.h \
    app/groupwork.h \
    app/imessagebox.h \
    app/mysqlsupport.h \
    app/pcm2play.h \
    app/protocolmessage.h \
    app/qmsqlquerymodel.h \
    app/qmtableviewdelegate.h \
    app/readypollinglistwork.h \
    app/socket.h \
    adddevicedialog.h \
    addduan_dialog.h \
    addoralterjiandialog.h \
    addpollingform.h \
    addquoralterdialog.h \
    addstationoralterdialog.h \
    adduserform.h \
    alterdevicedialog.h \
    alterpollingform.h \
    alteruserform.h \
    deluserdialog.h \
    devicecontrolform.h \
    deviceinfodialog.h \
    devicemanagementform.h \
    devicepollingform.h \
    dialog.h \
    doublecleckedform.h \
    duanalterdialog.h \
    duandialog.h \
    faultsearchdialog.h \
    logindialog.h \
    mainwindow.h \
    realtimedevicecontrolform.h \
    realtimemonitoring.h \
    sysmanagementform.h \
    troublelogform.h \
    userinfoform.h \
    userlogform.h \
    realtimework.h \
    app/md5.h

FORMS    += mainwindow.ui \
    devicecontrolform.ui \
    adddevicedialog.ui \
    logindialog.ui \
    deviceinfodialog.ui \
    devicemanagementform.ui \
    duandialog.ui \
    alterdevicedialog.ui \
    duanalterdialog.ui \
    adduserform.ui \
    alteruserform.ui \
    deluserdialog.ui \
    userlogform.ui \
    addpollingform.ui \
    doublecleckedform.ui \
    alterpollingform.ui \
    userinfoform.ui \
    troublelogform.ui \
    sysmanagementform.ui \
    devicepollingform.ui \
    app/company_about.ui \
    app/imessagebox.ui \
    addduan_dialog.ui \
    addoralterjiandialog.ui \
    addquoralterdialog.ui \
    dialog.ui \
    addstationoralterdialog.ui \
    faultsearchdialog.ui \
    realtimedevicecontrolform.ui

DISTFILES += \
    app/ReadMe.txt \
    app/global. cpp \
    image/fontawesome-webfont.ttf \
    image/qt_zh_CN.qm \
    image/house/1.jpg \
    image/house/10.jpg \
    image/house/11.jpg \
    image/house/2.jpg \
    image/house/3.jpg \
    image/house/4.jpg \
    image/house/5.jpg \
    image/house/6.jpg \
    image/house/7.jpg \
    image/house/8.jpg \
    image/house/9.jpg \
    image/room/back.jpg \
    image/room/Deluxe Suite.jpg \
    image/room/double room.jpg \
    image/room/single room.jpg \
    image/database/database.png \
    image/roomnum/1.png \
    image/roomnum/2.png \
    image/roomnum/3.png \
    image/roomnum/4.png \
    image/roomnum/5.png \
    image/roomnum/6.png \
    image/roomnum/7.png \
    image/roomnum/8.png \
    image/roomnum/9.png \
    image/roomnum/layout.png \
    image/roomtype/double.png \
    image/roomtype/luxury.png \
    image/roomtype/president.png \
    image/roomtype/signal.png \
    image/qss/black.css \
    image/qss/blue.css \
    image/qss/blue123.css \
    image/qss/brown.css \
    image/qss/darkgray.css \
    image/qss/dev.css \
    image/qss/deviceControl.css \
    image/qss/global.css \
    image/qss/gray.css \
    image/qss/lightgray.css \
    image/qss/silvery.css

RESOURCES += \
    image.qrc

include(qntp/qntp.pri)
