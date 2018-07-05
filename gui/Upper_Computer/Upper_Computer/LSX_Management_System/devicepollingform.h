#ifndef DEVICEPOLLINGFORM_H
#define DEVICEPOLLINGFORM_H

#include <QWidget>
#include <app/global.h>
#include <QComboBox>
#include "addpollingform.h"
#include "doublecleckedform.h"
#include "alterpollingform.h"
#include "app/imessagebox.h"
#include <QTcpSocket>
#include <QTimer>
#include <QHostAddress>
#include <QSqlError>
#include <QDateTime>
#include "app/readypollinglistwork.h"
#include  <QThread>
#include "app/groupwork.h"
#include <QAction>
#include "realtimedevicecontrolform.h"
#include <QMap>
#include <qiterator.h>
#include "realtimework.h"
#define  LISTEN 1
#define FAULT 2

//Device socket MAP_KEY class
class A_DEVICE_SOCKET
{
public:
   int type;
   QString Duan;
   QString Jian;
   QString Qu;
   QString Station;
   QString Deviceid;
   bool operator < (const A_DEVICE_SOCKET & s) const
   {
       qDebug()<<"A_DEVICE_SOCKET"<<s.type<<s.Duan<<s.Jian<<s.Qu<<s.Station<<s.Deviceid;
       return this->type <s.type;
   }
};

class A_DEVICE_INFO
{
public:
//   QTcpSocket * Socket;
   QString Ip;
   QString Port;
   inline void operator =(const A_DEVICE_INFO & deviceInfo)
   {
        this->Ip = deviceInfo.Ip;
        this->Port = deviceInfo.Port;
//        this->Socket = deviceInfo.Socket;
   }
};



namespace Ui {
class DevicePollingForm;
}

class DevicePollingForm : public QWidget
{
    Q_OBJECT

public:
    explicit DevicePollingForm(QWidget *parent = 0);
    ~DevicePollingForm();

    void sleep(unsigned int msec) ;


public:
    void startPolling();
    void addComboboxString();
    void addComboboxString(QString selectText,QComboBox *box,int indexComboBox);
    QString flushOperation();
    void setTableviewRightClikedMenu();
    void startThreadForEveryCheckDevice();
//    A_DEVICE_INFO getCheckDeviceInfo(QString duan, QString jian, QString qu, QString station, QString deviceid);//Ip and Port
//    QTcpSocket * getVoiceDeviceSocekt(QString duan, QString jian, QString qu, QString station, QString deviceid);//右击后获取socket信息传送给语音



signals:
    void toAddPolling(QString *string);
    void toDoubleClecked(QString * string);
    void toAlterPolling(QString * string);
    void toReadyPollingListForStopThread();
    void toGroupWorkStopPollingDevice();
    void toRealTimeDeviceControlForm(QTcpSocket*,QString deviceInfo[8]);
    void toRealTimeWorkForDeviceInfo(QTcpSocket * ,QString,QString);
    void toRealTimeDeviceControlFormForGotoProtocolMessage(QTcpSocket * socket);

    void toMainWindowForDeviceInfo(QString * string,bool);



public slots:
    void fromAddpolling_addOk();
    void fromMainWindowForAccessControl(bool userAccessType);
    void fromAlterPollingForClearUserSelectConotrol();
    void fromReadyPollingListForChoiceOK();
    void clearListThread();
    void clearWorkThread();
    void fromMainWindowForStartPolling();//先开启ui在开启巡检列表，让ui尽快的启动完毕
    void playVoice();
    void faultInfo();
//    void fromRealTimeWorkForRecordSocketToMap(QTcpSocket *socket);
//    void fromRealTimeWorkForGotoRealTimeForm(QTcpSocket *socket);

private slots:


    void defaultInitAllComboBox();
    void initOtherComboBom_Jian(QString);
    void  initOtherComboBom_Qu(QString);
    void initOtherComboBom_Station(QString);
    void initOtherComboBom_Device(QString);
    void setTableView(QString);

    void on_pushButton_2_clicked();


    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_tableView_pressed(const QModelIndex &index);

    void on_pushButton_clicked();

//    void on_pushButton_4_clicked();
//    void on_pushButton_5_clicked();
//    void on_pushButton_6_clicked();


    void initCombobox();
    void addCombobox_X_data(QComboBox * combox,QString sql,int);
    void setTableView();



    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_comboBox_3_activated(const QString &arg1);

    void on_comboBox_4_activated(const QString &arg1);

    void on_comboBox_5_activated(const QString &arg1);

    void on_checkBox_clicked(bool checked);


private:
    Ui::DevicePollingForm *ui;
    QString duan;
    QString jian;
    QString qu;
    QString station;
    QString device;
     int first;
     global *globalSql ;

    QString forJian_Duan;
    QString forQu_Jian;
    QString forStation_Qu;
    QString forDevice_Station;//车站当前选择项    *全部*/ui->combobox->currentText();
    QString forDevice;//设备当前选择
    QString comBox;
    QString comBox1;
    QString comBox2;
    QString comBox3;
    QString comBox4;
    QString comBox5;
     int allControlFlag;

     QString allControlString;

     QString defaultBoxString[4];
     int allControlTableViewFlag;
    addPollingForm * addPollingdevice;
    alterPollingForm * alterPollingdevice;
    doubleCleckedForm * doubleClecked;
    QSqlQueryModel  * queryModel;

    QString toDoubleCleckedString[5];
    QString toCleckedString[8];
    bool cleckedFlag ;
    bool userAccessControl;//控制不同用户的操作权限
    QTcpSocket local_Socekt;
    QTcpSocket connect_Socket;
    QTimer checkSocketStatusTimer;
    QTimer checkPollingOneTimer;
    int  checkPollingOneTimes;//一台设备检测五次

//    Wait_Device wait_Device;//下一次要执行检测的设备

//    QList<Device_Info> sameDevice;//下次执行检测时间相同的设备

    bool checkOver;

    //polling列表
    QThread * listThread;//列表线程
    readypollinglistwork *readyWork;//探测对象
    QThread * workThread;
    groupwork * work;

    int startPollingControlFlag;


    QAction * playDeviceVoice;
    QAction * faultDeviceInfo;

     RealTimeDeviceControlForm * voice;//实时监控语音调听

     QMap<A_DEVICE_SOCKET,QTcpSocket *>Device_Socket_Map;//All device socket map;
      A_DEVICE_SOCKET Device_Socket_Key;//device socket key;

      A_DEVICE_INFO deviceInfo;// 一个线程连接一个设备的信息  ip port socket socket 会添加到map 用于语音调听服务
//      RealTimeWork * realTimeWork;//实际的工作对象
};

#endif // DEVICEPOLLINGFORM_H
