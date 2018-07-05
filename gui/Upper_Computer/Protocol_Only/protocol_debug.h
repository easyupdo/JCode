#ifndef PROTOCOL_DEBUG_H
#define PROTOCOL_DEBUG_H

#include <QDialog>
#include <QTcpSocket>
#include <QTcpServer>
#include <protocolmessage.h>
#include "net_set.h"

namespace Ui {
class Protocol_Debug;
}

class Protocol_Debug : public QDialog
{
    Q_OBJECT

public:
    explicit Protocol_Debug(QWidget *parent = 0);
    ~Protocol_Debug();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

public slots:
    void setNet(QString ip,int port);

    void showMD5(QString s_MD5,int index);

    void delNetSetObj()
    {
        delete netSet;
    }




private:
    Ui::Protocol_Debug *ui;
    QTcpSocket * socket;
    ProtocolMessage * msg;
    Net_Set * netSet;
    QString connectIp;
    int connectPort;
};

#endif // PROTOCOL_DEBUG_H
