#ifndef REALTIMEMONITORING_H
#define REALTIMEMONITORING_H

#include <QAbstractItemModel>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
class realTimeMonitoring : public QObject
{
    Q_OBJECT

public:
    explicit realTimeMonitoring(QObject *parent = 0);
    void doConnectDevice();

private:
    QTcpSocket connSocket;
};

#endif // REALTIMEMONITORING_H
