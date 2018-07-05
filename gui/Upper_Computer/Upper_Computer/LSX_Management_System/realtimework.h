#ifndef REALTIMEWORK_H
#define REALTIMEWORK_H

#include <QAbstractItemModel>
#include <QTcpSocket>
#include <QTcpServer>
#include <QCoreApplication>
#include <QTimer>
#include <QTime>
#include "app/protocolmessage.h"

class RealTimeWork : public QObject
{
    Q_OBJECT

public:
    explicit RealTimeWork(QObject *parent = 0);
    void A_Device_Connect();
    void setDeviceConnectInfo(QString, QString);
    void sleep(unsigned int msec);
    void checkSocketStatus();

   signals:
    void toDevicePollingFormForRecordSocketToMap(QTcpSocket * socket);
    void toProtocolMessageForSocket(QTcpSocket * socket);
    void toDevicePollingForGotoRealTimeFrom(QTcpSocket * socket);
public slots:
    void fromProtocolMessageForVerifyVoiceRecordMD5();

private:
    QTcpSocket * socket;
    QString ip;
    QString port;

    ProtocolMessage *realTimeMSG;//用于md5认证、连接保活
};

#endif // REALTIMEWORK_H
