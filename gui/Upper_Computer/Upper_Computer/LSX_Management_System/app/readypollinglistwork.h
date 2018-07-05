#ifndef READYPOLLINGLISTWORK_H
#define READYPOLLINGLISTWORK_H
#include <QObject>
#include <QSqlQuery>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include "app/groupwork.h"
#include <QThread>
#include <QCoreApplication>
#include  <QSqlDatabase>
#define THREAD_GROUP_NUM 2500

//typedef struct DEVICE_INFO
//{
//    QString duan;
//    QString jian;
//    QString qu;
//    QString station;
//    QString deviceid;
//    QString span;
//    QDateTime nextCheckTime;
//}Device_Info;


class readypollinglistwork:public QObject
{
    Q_OBJECT
public:
    readypollinglistwork();
    void readyPollingList();
    void choiceOneDevicePolling();//从检测表中选择时间最小的设备
    void setDeviceNextPollingTime( Device_Info & device);
    void sleep(unsigned int msec);
    void initListDB();
    void clearDB();

    signals:
//    void toFroupWorkForDoCheckWork(QList<Device_Info>list,int second);
    void toDevicePollingForChoiceOK();
    void toGroupWorkForSentGroupSanmeDevice(QList<Device_Info>groupDevice);
public slots:
    void pollingTimeOut();
    void readySameDeviceListReadyStartThread();
    void fromDevicePollingFormForStopThread();

public:
    QList<Device_Info> allSameDevice;//下次执行检测时间相同的设备
    QList<Device_Info> groupSameDevice;//一组检测时间相同的设备

    int startPollingTime;


    QString  searchDeviceMinTime;

     QTimer  *threadTimer;

     bool stopFlag;
     int delThreadTimerFlag;//0:初始状态  1:时间表没有更新完 结束    2:时间表跟新完进入选择巡检结束
    bool pollingOverFlag;
    QSqlDatabase listDB;


//    void
};

#endif // readypollinglistwork_H
