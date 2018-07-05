#include "readypollinglistwork.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QMutex>
//#define DEBUG

readypollinglistwork::readypollinglistwork()
{
    startPollingTime = 0;
    stopFlag = false;
    delThreadTimerFlag = 0;
    pollingOverFlag = false;
    initListDB();
}


//准备好列表
void readypollinglistwork::readyPollingList()//
{

        qDebug()<<QString::fromLocal8Bit("检测列表线程::")<<this->thread();
        Device_Info device;
        {//控制作用域
            QSqlQuery query(QSqlDatabase::database("LISTDB"));

            query.exec("select * from `check`where duan = 'ceshi'");
            while(query.next())
            {
                if(query.value(12).toDateTime().toTime_t() <= QDateTime::currentDateTime().toTime_t())//如果记录时间小于当前时间 更新下次检查时间    否则 无需更新用的时间是下次执行时间
               {
        //            qDebug()<<"duan:"<<query.value(1).toString()<<"deviceid:"<<query.value(5).toString()<<"historytime:"<<query.value(12).toString();
        //            qDebug()<<QString::fromLocal8Bit("当前时间:")<<QDateTime::currentDateTime().toTime_t();
        //            qDebug()<<QString::fromLocal8Bit("记录时间:")<<query.value(12).toDateTime().toTime_t();
                    int alterTime = (QDateTime::currentDateTime().toTime_t() - query.value(12).toDateTime().toTime_t());
        //            qDebug()<<"Alter Time :"<<alterTime;
                    int t = (query.value(7).toInt()*3600);
        //            qDebug()<<"t:"<<t;
                    int T = alterTime/t + 1;
        //            qDebug()<<QString::fromLocal8Bit("增加span次数")<<T;
        //            system("pause");
                    QDateTime nextCheckTime =QDateTime::fromTime_t(query.value(12).toDateTime().toTime_t() + query.value(7).toInt() *T* 3600);
        //            qDebug()<<QString::fromLocal8Bit("修正时间")<<nextCheckTime.toString();
                    device.duan=query.value(1).toString();
                    device.jian = query.value(2).toString();
                    device.qu = query.value(3).toString();
                    device.station = query.value(4).toString();
                    device.deviceid = query.value(5).toString();
                    device.nextCheckTime = nextCheckTime;
                    device.span = query.value(7).toString();
            //        setDeviceLastPollingTime(device);
                    setDeviceNextPollingTime(device); //更新下次检测时间
                    if(stopFlag)
                    {
                        qDebug()<<QString::fromLocal8Bit("停止sql操作");
                        delThreadTimerFlag = 1;
                        break;
                    }
               }
            }
            if(!stopFlag)
            {
                choiceOneDevicePolling();//
                sleep(3000);
                delThreadTimerFlag = 2;//释放timer
            }
        }


        pollingOverFlag = true;
        qDebug()<<QString::fromLocal8Bit("结束列表sql操作")<<delThreadTimerFlag;
        clearDB();

}

void readypollinglistwork::setDeviceNextPollingTime( Device_Info & device)
{
    {
        QSqlQuery query(QSqlDatabase::database("LISTDB"));
        QString sql = QObject::tr("update `check` set historytime = '%1' where duan  = '%2' and jian = '%3' and qu = '%4' and station = '%5' and deviceid = '%6'").arg(device.nextCheckTime.toString("yyyy-MM-dd hh:mm:ss"),device.duan,device.jian,device.qu,device.station,device.deviceid);
        query.prepare(sql);
        qDebug()<<"SQL:"<<sql;
        if(query.exec())
        {
            qDebug()<<"update successful!";
        }else
            qDebug()<<"update failed";
    }
    clearDB();

}


void readypollinglistwork::choiceOneDevicePolling()//从检测表中选择时间最小的设备
{

    qDebug()<<QString::fromLocal8Bit("选择一个设备");
    //当前检索列表中时间最小的设备
//    iMessageBox box;
    {
        QSqlQuery query(QSqlDatabase::database("LISTDB"));
        QString sql = "select * from `check` where duan = 'ceshi' order by historytime asc limit 0,1";//以下一次执行检查为坐标 选择最小的时间点设备historytime 为这个检测的依据，asc 查询最小的
        query.prepare(sql);
        qDebug()<<QString::fromLocal8Bit("选择时间最小的设备SQL:")<<sql;
        if(query.exec())
        {
            while(query.next())
            {
                qDebug()<<"QQQQQQQQ"<<query.value(12).toString();
                int time_Interval = query.value(12).toDateTime().toTime_t() - QDateTime::currentDateTime().toTime_t();
                startPollingTime = time_Interval;
                qDebug()<<"set Time:"<<query.value(12).toDateTime().toTime_t();//下次执行时间 整个的巡检都是依照historytime来计算下次执行时间
                qDebug()<<"now Time:"<<QDateTime::currentDateTime().toTime_t();

                qDebug()<<QString::fromLocal8Bit("最小时间设备SQL:")<<sql<<QString::fromLocal8Bit("索引号:")<<query.value(0).toString();
                qDebug()<<"time_Interval:"<<time_Interval;
                searchDeviceMinTime = query.value(12).toDateTime().toString();
                if(time_Interval < 0)
                {
                    qDebug()<<QString::fromLocal8Bit("计时器不可用重新获取计时器时间!");
                    readyPollingList();
                    choiceOneDevicePolling();
                    break;
                }
                threadTimer = new QTimer;//开始探测计时器
                connect(threadTimer,&QTimer::timeout,this,&readypollinglistwork::readySameDeviceListReadyStartThread);
                threadTimer->start(startPollingTime*1000);
    #ifdef DEBUG
                qDebug()<<QString::fromLocal8Bit("准备分配工作线程倒计时开始:")<<startPollingTime;
                sleep(2000);
    #endif
            }
        }else
        {
            qDebug()<<QString::fromLocal8Bit("选择一个设备执行SQL失败:")<<query.lastError().nativeErrorCode()<<query.lastError().text();
    //        box.setUserMessage(QString::fromLocal8Bit("执行错误! 错误代码:") + query.lastError().nativeErrorCode(),"error");
    //        box.exec();
        }
        //准备好列表后开始 探测所有的线程的状态
    }
    clearDB();

}


void readypollinglistwork::sleep(unsigned int msec)  //延时
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}



void readypollinglistwork::pollingTimeOut()
{
//    timer.stop();
}

void readypollinglistwork::readySameDeviceListReadyStartThread()
{
    delThreadTimerFlag = 3;
    threadTimer->stop();
    delete threadTimer;
//    delThreadTimerFlag = 3;

//    QMutex qmutex;
    //测试相同设备计数
    int sameDeviceAccount = 0;
    {
#ifdef DEBUG
        qDebug()<<QString::fromLocal8Bit("开始分配工作线程");
        sleep(2000);
#endif
    }

    {
        //关闭准备列表线程的计时器 由于在线程中只能使用 new 注意 释放内存
//        threadTimer->stop();
//        delete threadTimer;
//        emit toDevicePollingForChoiceOK();
    }
    int TEST = 0;
    QList<QThread*>pollingListThreadList;
    {//下次执行检测的时间相同的话放到一个列表中去
        groupSameDevice.clear();
        QSqlQuery sameQuery(QSqlDatabase::database("LISTDB"));
        qDebug()<<QString::fromLocal8Bit("开始时间:")<<searchDeviceMinTime;
        qDebug()<<QString::fromLocal8Bit("五分钟后时间:")<<QDateTime::fromTime_t(QDateTime::fromString(searchDeviceMinTime).toTime_t() + 300).toString();
        QString sameSQL = QObject::tr("select duan,jian,qu,station,deviceid,span,historytime from `check` where historytime between '%1' and '%2' ").arg(QDateTime::fromString(searchDeviceMinTime).toString("yyyy-MM-dd hh:mm:ss"),QDateTime::fromTime_t(QDateTime::fromString(searchDeviceMinTime).toTime_t() + 300).toString("yyyy-MM-dd hh:mm:ss"));//距离最小时间后五分钟内的设备都添加到巡检列表中
        sameQuery.exec(sameSQL);
        qDebug()<<"sameSQL:"<<sameSQL;
        qDebug()<<"sameLastError:"<<sameQuery.lastError().nativeErrorCode()<<sameQuery.lastError().text();
        int account = 0;
        while(sameQuery.next())
        {
//            sleep(1000);
            sameDeviceAccount +=1;
            account+=1;
            Device_Info sameD;//一个设备的信息
            sameD.duan = sameQuery.value(0).toString();
            sameD.jian = sameQuery.value(1).toString();
            sameD.qu = sameQuery.value(2).toString();
            sameD.station = sameQuery.value(3).toString();
            sameD.deviceid = sameQuery.value(4).toString();
            sameD.nextCheckTime = QDateTime::fromString(searchDeviceMinTime);
            sameD.span = sameQuery.value(6).toString();

            groupSameDevice.append(sameD);//添加到相同时间的QList中 //这是相同设备线程分组的设备
//            qDebug()<<QString::fromLocal8Bit("相同设备中一个设备的信息:")<<sameD.duan<<sameD.jian<<sameD.qu<<sameD.station<<sameD.deviceid<<sameD.nextCheckTime<<sameD.span;
//                    groupSameDevice.insert(1,sameD);
//            qDebug()<<QString::fromLocal8Bit("当前account的值:")<<account;
            if(account == THREAD_GROUP_NUM)
            {
                //TODO
                //多线程版本
            }
        }
        qDebug()<<QString::fromLocal8Bit("相同设备一共计数:")<<sameDeviceAccount;
        if(account < THREAD_GROUP_NUM && account > 0)
        {
            qDebug()<<QString::fromLocal8Bit("找不到BUG好烦啊");
            emit toGroupWorkForSentGroupSanmeDevice(groupSameDevice);//准备好列表就可以 继续准备下一次的列表
        }
    }
    clearDB();

    qDebug()<<QString::fromLocal8Bit("子线程计数:")<<pollingListThreadList.size();
    qDebug()<<QString::fromLocal8Bit("准备列表进程 等待子进程结束");


//    }
//    system("pause");
    //所有子进程结束后 就可以准备下次要探测的设备的列表了
    qDebug()<<QString::fromLocal8Bit("告诉准备列表线程准备下一批要探测的设备");
//    emit toDevicePollingFormForReadyNextPollingList(index);//index:本线程检测列表的个数
}

void readypollinglistwork::fromDevicePollingFormForStopThread()
{
    qDebug()<<QString::fromLocal8Bit("直连清除:");
//    this->thread()->killTimer(1);
    stopFlag = true;
    while(1)
    {

        if(delThreadTimerFlag == 1)
        {
            qDebug()<<QString::fromLocal8Bit("没有开启Timer 退出线程");
            delThreadTimerFlag = 0;
            this->thread()->quit();
            break;
        }else if(delThreadTimerFlag == 2)
        {
            qDebug()<<QString::fromLocal8Bit("开始释放");
//            threadTimer->stop();
            qDebug()<<QString::fromLocal8Bit("停止threadTimer");
//            delete threadTimer;
            qDebug()<<QString::fromLocal8Bit("删除threadTimer");
            delThreadTimerFlag = 0;
            qDebug()<<QString::fromLocal8Bit("连接的数据库名字:")<<listDB.connectionNames();
            this->thread()->quit();
            qDebug()<<QString::fromLocal8Bit("t停止定时器");
            qDebug()<<QString::fromLocal8Bit("清除List 线程中的定时器 准备退出List线程");
            qDebug()<<QString::fromLocal8Bit("List线程收到终止线程信号:");
            break;
        }else if(delThreadTimerFlag == 3)//在定时器到时间的时候已经清除过了
        {
            qDebug()<<QString::fromLocal8Bit("清清清清清清清清清清清清清清");
            delThreadTimerFlag = 0;

            qDebug()<<QString::fromLocal8Bit("连接的数据库名字:")<<listDB.connectionNames();
            this->thread()->quit();
            break;
        }
        qDebug()<<QString::fromLocal8Bit("等待sql循环结束标志");
        sleep(1000);
    }

}


void readypollinglistwork::initListDB()
{
//        listDB = QSqlDatabase::addDatabase("QMYSQL","LISTDB");
//        listDB.setHostName("127.0.0.1");
//        listDB.setUserName("root");
//        listDB.setPassword("123456");
//        listDB.setDatabaseName("hm");
//        if(listDB.open())
//        {
//            qDebug()<<QString::fromLocal8Bit("List Thread 数据库连接成功");
//            qDebug()<<QString::fromLocal8Bit("数据库连接名字:")<<listDB.connectionNames();
//        }else
//        {
//            qDebug()<<QString::fromLocal8Bit("List Thread 数据库连接失败!");
//        }
}


void readypollinglistwork::clearDB()
{
    listDB.close();
    QSqlDatabase::removeDatabase("LISTDB");
}


