#ifndef GROUPWORK_H
#define GROUPWORK_H
#include <QObject>
#include <QTcpSocket>
//#include "app/readypollinglistwork.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QMetaType>//自定义结构
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>
#include <QNetworkConfigurationManager>
#include <QSqlDatabase>
#define CHECK_SUCCESS 1
#define CHECK_FAIL 2


typedef struct DEVICE_TO_LOCAL
{
    QString duan;
    QString jian;
    QString qu;
    QString station;
    QString deviceid;
}OneDevice;

typedef struct DEVICE_INFO
{
    QString duan;
    QString jian;
    QString qu;
    QString station;
    QString deviceid;
    QString span;
    QDateTime nextCheckTime;
}Device_Info;

typedef struct POLLING_DEVICE
{
    QString duan;
    QString jian;
    QString qu;
    QString station;
    QString deviceid;
    QDateTime historytime;
    int span;
    QString Device_IP;
    QString Device_PORT;
    int Device_Time;//还差多少时间到检测时间 定时器的倒计时,草不改了 增加
}Wait_Device;//该结构用来记录下次将要检测的设备信息

class groupwork:public QObject
{
    Q_OBJECT
public:
    groupwork();
    void doCheckWork();
    void checkPollingOne(QList<Device_Info> sameDevice);
    void updateCurrentDevcieNextPollingTime(Wait_Device wait_Device,int checkState);
    void writePollingInfoToLog(OneDevice oneDevice, QString checkResult,int faulttype);
    void sleep(unsigned int msec);
    void initWorkThreadDB();
    void clearWorkDB();

private slots:
    void checkSocketConnectStatus();
public slots:
    void doWork();
    void check();
    void fromReadyPollingListWorkForRecvGroupSanmeDevice(QList<Device_Info> groupDevice);
    void fromDevicePollingForGroupWorkStopPollingDevice();

signals:
    void toDevicePollingFormForReadyNextPollingList(int num);//检测本线程num个数的设备，检测完后发送给devicePollingForm告知结束，当所有线程都结束readypollingList准备新的

    void toFroupWorkForDoCheckWork(QList<Device_Info>list,int second);

private:
    Wait_Device wait_Device;//下一次要执行检测的设备
    QList<Device_Info> sameDevice;//下次执行检测时间相同的设备

    QTcpSocket *local_Socekt;
    QTimer *getConnectStatusTimer;
    bool checkOver;

    QList<Device_Info>groupList;
public:
//    QMutex *qmutex;
    QSqlDatabase workDB;
    bool stopWorkThreadFlag;
    bool quitOkFlag;

};

#endif // GROUPWORK_H
