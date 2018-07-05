#include "groupwork.h"
#include <QDebug>
#include <QList>
#include <QTimer>
#include <QThread>
#include <QHostAddress>
#include <QSqlError>
groupwork::groupwork()
{
    qRegisterMetaType<QList<Device_Info>>("QList<Device_Info>");
    checkOver = true;
    stopWorkThreadFlag = false;
    quitOkFlag = true;
}


void groupwork::doWork()
{
    qDebug()<<QString::fromLocal8Bit("测试线程信号!");
}


void groupwork::doCheckWork()//参数1：该线程要检测的设备列表   2：检测倒计时
{
    qDebug()<<QString::fromLocal8Bit("子线程开始")<<this->thread();
    qDebug()<<QString::fromLocal8Bit("一个探测线程的设备数量:")<<groupList.size();
    for(int i = 0;i<groupList.size();i++)
    {
        qDebug()<<"List:"<<groupList.value(i).duan<<groupList.value(i).jian<<groupList.value(i).qu<<groupList.value(i).station<<groupList.value(i).deviceid<<groupList.value(i).nextCheckTime<<groupList.value(i).span;

    }
//    system("pause");
//    sleep(5000);
//    while(1)
//    {
//        qDebug()<<QString::fromLocal8Bit("这是子线程正在运行 线程id:")<<this->thread();
//        sleep(1000);
//    }
    checkPollingOne( groupList);


    qDebug()<<QString::fromLocal8Bit("doCheckWork is over!");

}

//检测下次计划检测的设备 包含相同时间待检测的设备 太多开线程
void groupwork::checkPollingOne(QList<Device_Info> sameDevice)
{
    Wait_Device Device;
    OneDevice oneDevice;
    local_Socekt = new QTcpSocket;
    qDebug()<<QString::fromLocal8Bit("创建Socket ID 号码 ")<<local_Socekt;
    qDebug()<<QString::fromLocal8Bit("groupList:")<<sameDevice.at(0).duan;

//    checkPollingOneTimer.stop();
    int index = sameDevice.size();
    qDebug()<<QString::fromLocal8Bit("一个探测线程需要探测的设备数:")<<index;

    for(int i = 0;i<index;i++)
    {
        if(stopWorkThreadFlag)
        {
            stopWorkThreadFlag = false;
            quitOkFlag = true;
            break;
        }
            qDebug()<<" noting to do"<<i<<QString::fromLocal8Bit("index:")<<index;

            qDebug()<<QString::fromLocal8Bit("开始探测一个");
            oneDevice.duan = Device.duan = sameDevice.at(i).duan;
            oneDevice.jian = Device.jian = sameDevice.at(i).jian;
            oneDevice.qu = Device.qu = sameDevice.at(i).qu;
            oneDevice.station = Device.station = sameDevice.at(i).station;
            oneDevice.deviceid = Device.deviceid = sameDevice.at(i).deviceid;
            Device.historytime = sameDevice.at(i).nextCheckTime;
            Device.span = sameDevice.at(i).span.toInt();

            //Device存放要检查的那一个的信息，用语在检查后更新时间
            {
                QSqlQuery deviceQquery(QSqlDatabase::database("WORKDB"));//根据check表中的设备信息获取该设备的ip和port信息
                QString deviceSQL = QString::fromLocal8Bit("select ip,port from device where duan ='%1' and jian = '%2' and qu = '%3' and station = '%4' and deviceid = '%5'").arg(sameDevice.at(i).duan,sameDevice.at(i).jian,sameDevice.at(i).qu,sameDevice.at(i).station,sameDevice.at(i).deviceid);
                qDebug()<<QString::fromLocal8Bit("即将上锁");

    //            this->qmutex->lock();
    //            QMutexLocker locker(qmutex);
                qDebug()<<QString::fromLocal8Bit("上锁");
                deviceQquery.prepare(deviceSQL);
                qDebug()<<"SQL:"<<deviceSQL;
                int ret = deviceQquery.exec();

                if(ret)
                {
                    while(deviceQquery.next())
                    {
                        ;
                        QString connectIp = deviceQquery.value(0).toString();
                        QString connectPort = deviceQquery.value(1).toString();
                        int ret = local_Socekt->isOpen();
                        if(ret)
                            qDebug()<<QString::fromLocal8Bit("套接字处于打开状态");
                        else
                            qDebug()<<QString::fromLocal8Bit("套接字处于关闭状态");
    //                    local_Socekt->waitForConnected(1000);
                        local_Socekt->disconnectFromHost();
                        local_Socekt->connectToHost(QHostAddress(connectIp),connectPort.toInt());//连接目标设备
                        qDebug()<<QString::fromLocal8Bit("连接socket ID 号码 ")<<local_Socekt;

                        qDebug()<<QString::fromLocal8Bit("目标检索设备信息:")<<connectIp<<connectPort<<QString::fromLocal8Bit("设备号:")<<Device.deviceid;
                        local_Socekt->waitForConnected(1000);
                        qDebug()<<QString::fromLocal8Bit("当前网络连接状态:")<<local_Socekt->state();
                        while(1)
                        {
                            if(local_Socekt->state() == QAbstractSocket::ConnectingState)
                            {
                                sleep(1000);
                                qDebug()<<QString::fromLocal8Bit("正在连接状态 .... ...... ...... ........... ");
                                continue;
                            }
                            else if(local_Socekt->state() == QAbstractSocket::UnconnectedState)
                            {
                                qDebug()<<QString::fromLocal8Bit("这个设备没有连接555555555555555555555555555");
                                        writePollingInfoToLog(oneDevice,QString::fromLocal8Bit("网络连接失败"),2);// 1:成功    2:失败
                                        updateCurrentDevcieNextPollingTime(Device,CHECK_SUCCESS);//It is ok haha//1:巡检成功    2：巡检失败
        //                        checkOver=true;
                                        break;
                            }else if(local_Socekt->state() == QAbstractSocket::ConnectedState)
                            {
                                qDebug()<<QString::fromLocal8Bit("这个设备有连接22222222222222222222222222");
                                writePollingInfoToLog(oneDevice,QString::fromLocal8Bit("网络连接成功了"),1);
                                updateCurrentDevcieNextPollingTime(Device,CHECK_FAIL);//It is ok haha
                                local_Socekt->disconnectFromHost();
                                break;
                            }
                        }
                    }
                } else
                {
                    qDebug()<<"TEST1 数据库执行出错:"<<deviceQquery.lastError().nativeErrorCode()<<deviceQquery.lastError().text();
                }
    //            this->qmutex->unlock();
                qDebug()<<QString::fromLocal8Bit("解锁");
            }
            clearWorkDB();

    }
    delete local_Socekt;
qDebug()<<QString::fromLocal8Bit("探测一组设备结束'");
//system("pause");
this->thread()->quit();
}


void groupwork::checkSocketConnectStatus()
{
    qDebug()<<QString::fromLocal8Bit("探测设备连接状态");
//    qDebug()<<local_Socekt.state();

//    if(local_Socekt.state() == QAbstractSocket::ConnectedState)
//    {
//        qDebug()<<QString::fromLocal8Bit("设备探测 连接成功");
//        local_Socekt.disconnectFromHost();
//        getConnectStatusTimer->stop();
//        checkOver = true;
//    }else if(local_Socekt.state() == QAbstractSocket::UnconnectedState)
//    {
//        qDebug()<<QString::fromLocal8Bit("执行探测 连接失败");

//        writePollingInfoToLog(QString::fromLocal8Bit("网络连接失败"));
//        updateCurrentDevcieNextPollingTime();//It is ok haha
//        checkOver = true;
//        getConnectStatusTimer->stop();
//          qDebug()<<QString::fromLocal8Bit("一个设备探测程结束了");
//    }
    getConnectStatusTimer->stop();
    delete getConnectStatusTimer;
    checkOver = true;

    qDebug()<<"checkOver == true";

}


//错误信息写入log
void groupwork::writePollingInfoToLog(OneDevice oneDevice, QString checkResult, int faulttype)
{

    qDebug()<<QString::fromLocal8Bit("设备信息是:")<<oneDevice.duan;
    qDebug()<<QString::fromLocal8Bit("设备信息是:")<<oneDevice.jian;
    qDebug()<<QString::fromLocal8Bit("设备信息是:")<<oneDevice.qu;
    qDebug()<<QString::fromLocal8Bit("设备信息是:")<<oneDevice.station;
    qDebug()<<QString::fromLocal8Bit("设备信息是:")<<oneDevice.deviceid;

//    sleep(3000);
    {
        QSqlQuery query(QSqlDatabase::database("WORKDB"));
//        QString sql = QObject::tr("insert into log(recorddate,operation) values('%1','%2')").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),checkResult);
        QString sql = QObject::tr("insert into fault(duan,jian,qu,station,deviceid,operation,opertype,recodertime) values('%1','%2','%3','%4','%5','%6','%7','%8')").arg(oneDevice.duan,oneDevice.jian,oneDevice.qu,oneDevice.station,oneDevice.deviceid,checkResult,QString::number(faulttype),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.prepare(sql);
        int ret = query.exec();
        if(ret)
            qDebug()<<QString::fromLocal8Bit("写入日志成功");
        else
            qDebug()<<QString::fromLocal8Bit("写入失败 错误代码:")<<query.lastError().nativeErrorCode()<<query.lastError().text();
    }
    clearWorkDB();

}


//更新下次该执行检测的时间
void groupwork::updateCurrentDevcieNextPollingTime(Wait_Device wait_Device, int checkState)
{
    qDebug()<<QString::fromLocal8Bit("检测的设备信息:")<<wait_Device.deviceid;
    qDebug()<<"                 ";
   {
        QSqlQuery query(QSqlDatabase::database("WORKDB"));
        QDateTime nextCheckTime =QDateTime::fromTime_t(wait_Device.historytime.toTime_t() + wait_Device.span * 3600);
        qDebug()<<QString::fromLocal8Bit("写入时间:")<<nextCheckTime.toString();
        QString sql = QObject::tr("update `check` set historytime = '%1',checkstate = '%2' where duan = '%3' and jian = '%4' and qu = '%5' and station = '%6' and deviceid = '%7'").arg(wait_Device.historytime.toString("yyyy-MM-dd hh:mm:ss"),QString::number(checkState),wait_Device.duan,wait_Device.jian,wait_Device.qu,wait_Device.station,wait_Device.deviceid);
        query.prepare(sql);
        if(query.exec())
        {
            qDebug()<<"exe SQL:"<<sql;
            qDebug()<<QString::fromLocal8Bit("当前方法所在线程:")<<this->thread();
        }
   }
    clearWorkDB();

}


void groupwork::sleep(unsigned int msec)  //延时
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void groupwork::check()
{

}


void groupwork::fromReadyPollingListWorkForRecvGroupSanmeDevice(QList<Device_Info>groupDevice)
{
    for(int i = 0; i< groupDevice.size();i++)
    {
        qDebug()<<QString::fromLocal8Bit("work1设置的一组设备:")<<groupDevice.value(i).deviceid;
        groupList.append(groupDevice.value(i));
    }
    qDebug()<<QString::fromLocal8Bit("当前所在线程id:")<<this->thread();
    doCheckWork();
}

void groupwork::fromDevicePollingForGroupWorkStopPollingDevice()
{
    qDebug()<<QString::fromLocal8Bit("终止work线程ASASASASASASASASASASAS!");
    stopWorkThreadFlag =true;
    while(1)
    {
//        qDebug()
        if(quitOkFlag)
        {
            quitOkFlag = false;
            qDebug()<<QString::fromLocal8Bit("跳出循环");
            break;
        }
        qDebug()<<QString::fromLocal8Bit("GoGOGoGoGoGo");
    }
    qDebug()<<QString::fromLocal8Bit("退出work线程");
    this->thread()->quit();
}


void groupwork::initWorkThreadDB()
{
    workDB = QSqlDatabase::addDatabase("QMYSQL","WORKDB");
    workDB.setHostName("127.0.0.1");
    workDB.setUserName("root");
    workDB.setPassword("123456");
    workDB.setDatabaseName("hm");
    if(workDB.open())
    {
        qDebug()<<QString::fromLocal8Bit("List Thread 数据库连接成功");
    }else
    {
        qDebug()<<QString::fromLocal8Bit("List Thread 数据库连接失败!");
    }
}


void groupwork::clearWorkDB()
{
    workDB.close();
    QSqlDatabase::removeDatabase("WORKDB");
}
