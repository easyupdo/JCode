#ifndef GLOBAL_H
#define GLOBAL_H
#include "mysqlsupport.h"
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QFile>

#define ERROR_PREPARE_SQL_LOG_GLOBAL    0   //第一步sql.repare()执行错误
#define ERROR_EXEC_SQL_LOG_GLOBAL         1   //sql.exec() error
#define ERROP_NEXT_SQL_LOG_GLOBAL         2   //sql.next() error

struct  combobox_Select
{
    QString sql_SelectDuan;
    QString sql_SelectJian;
    QString sql_SelectQu;
    QString sql_SelectStation;
};


class global:public QObject
{
    Q_OBJECT

public:
    global(QObject * parent = 0);
    ~global();
public:
    QString returenComBoxCurrentText(QString,int);
    bool logSelectFromUserModel(QString);
    QString log_SQL(int);
    QString log_SQL_UseridModel_Select(QString,int);
    QString log_SQL_UseridModel_Select(QString startTime,QString endTime); //re

    /*alterDevice*/
    QString addDevice_SQL_Select(QString *,int);
    QString addDeviceToMysql(QString *);
    QString alterDeviceToMysql(QString *string);
    QString delDeviceFromMysql(QString *);

    //style
    void setStyle(const QString &StyleName);

//    void checkDB(MysqlSupport &global);



    QString sql_SelectDuan;
    QString sql_SelectJian;
    QString sql_SelectQu;
    QString sql_SelectStation;
    QString sql_SelectDevice;
    QString sql_UpdateCombox;

    QString sql_PollingSelectDuan;
    QString sql_PollingSelectJian;
    QString sql_PollingSelectQu;
    QString sql_PollingSelectStation;
    QString sql_PollingSelectDevice;
public slots:
    void fromUserSqlClassForCheckDB();


/********************写 log*********************
//public:
//    template<class T>
//    void LSX_log(T log);
**********************写log********************/


public:
    /*LOG*/
    QSqlQueryModel * queryUserModel;
};
/********************写 log*********************
//template<class T>
//void global::LSX_log(global::T log)
//{
//    QString fileName = QApplication::applicationDirPath() + "/log.txt";
//    qDebug()<<"FFFFFFF:"<<fileName;
//    QFile write_file(fileName);
//    write_file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);
////    QByteArray num = QString::number(net_account).toLatin1() + ">";
//    // QStringList driverList
//    qDebug<<T;
//    //    if()
////    for()

//    write_file.write(l);
//    write_file.close();
//}
**********************写log********************/

#endif // GLOBAL_H
