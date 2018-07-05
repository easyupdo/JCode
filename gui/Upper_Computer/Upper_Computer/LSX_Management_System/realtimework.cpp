#include "realtimework.h"

RealTimeWork::RealTimeWork(QObject *parent)
    : QObject(parent)
{

}

void RealTimeWork::A_Device_Connect()
{
    this->socket->disconnectFromHost();
    qDebug()<<QString::fromLocal8Bit("Socket address:")<<this->socket;
    this->socket->connectToHost(this->ip,this->port.toInt());
//    sleep(3000);
    qDebug()<<QString::fromLocal8Bit("当前设备网络连接状态:")<<this->socket->state();
    QTimer  *socketStatusTimer = new QTimer;
    connect(socketStatusTimer,&QTimer::timeout,this,&RealTimeWork::checkSocketStatus,Qt::DirectConnection);
    socketStatusTimer->start(1000);
    while(1)
    {
        sleep(1000);
        if(this->socket->state() == QAbstractSocket::ConnectedState)
        {
           //发送给pollingFrom中socket和发送给realtimeFrom的信号】
            qDebug()<<QString::fromLocal8Bit("第一步信号");
            emit toDevicePollingForGotoRealTimeFrom(this->socket);

            break;
        }
    }

//    while(1)
//    {
//        sleep(2000);
//    }
}

void RealTimeWork::setDeviceConnectInfo(QString ip, QString port)
{
    socket = new QTcpSocket;
    qDebug()<<QString::fromLocal8Bit("当前线程:")<<this->thread()<<"socket thread:"<<socket->thread();
    this->ip = ip;
    this->port = port;
    qDebug()<<QString::fromLocal8Bit("线程对象类:")<<this->socket<<this->ip<<this->port;
    emit toDevicePollingFormForRecordSocketToMap(socket);//发送给DevicePollingForm记录socket导map中去
    A_Device_Connect();
}

void RealTimeWork::sleep(unsigned int msec)  //延时
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void RealTimeWork::checkSocketStatus()
{
    if(this->socket->state() == QAbstractSocket::ConnectedState)
    {
        //由于 不能跨线程使用socket
        qDebug()<<QString::fromLocal8Bit("当前网络连接:");
//        qDebug()<<QString::fromLocal8Bit("M_800C")<<realTimeMSG->M_800C;
        this->socket->write(realTimeMSG->M_800C);
//        qDebug()<<QString::fromLocal8Bit("当前所在线程id:")<<this->socket->thread()<<"socket addressNOW:"<<socket;
    }
    if(this->socket->state() == QAbstractSocket::UnconnectedState)
    {
        qDebug()<<QString::fromLocal8Bit("网络未连接,请检查设备!");
    }
//    socketStatusTimer.stop();
}

void RealTimeWork::fromProtocolMessageForVerifyVoiceRecordMD5()
{
    qDebug()<<QString::fromLocal8Bit("服务器MD5通过验证记录仪MD5");
    this->socket->write(realTimeMSG->M_801C);
    qDebug()<<QString::fromLocal8Bit("SSSSSSsocket")<<this->socket<<this->socket->state();
}

