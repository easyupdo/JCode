#include "realtimemonitoring.h"

realTimeMonitoring::realTimeMonitoring(QObject *parent)
    : QObject(parent)
{

}


void realTimeMonitoring::doConnectDevice()
{
    QTcpSocket * connectSocket;
    QString connectIP;
    QString connectPORT;
    connectSocket->connectToHost(QHostAddress(connectIP),connectPORT.toInt());
}

