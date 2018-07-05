
/*
 * ERROR:命名规则
    ERROR_操作_使用地方标识_模块标识_使用文件标识；
    例如：
    ERROR_PREPARE_SQL_GLOBAL  : 错误_sql.prepare()_SQL语句_global文件
*/


/*
 * 各个模块方法名:命名规则logSelectFromUserModel
 * 方式1：模块_操作      log_SelectFromUserModel_XXX
 * 方式2：模块_操作_触发组件名称  log_SelectFromUserModel_查询按钮 : log模块 的 选择用户模式 由 查询按钮触发
*/



#include "global.h"
#include <QFile>
#include <QApplication>

global::global(QObject *parent):QObject(parent)
{
//    this-
    //sql_init
    sql_SelectDuan    = "select * from duan";
    sql_SelectJian     = "select * from jian where duan =:user_select";
    sql_SelectQu      = "select * from qu where jian = :user_select";
    sql_SelectStation = "select * from station where qu = :user_select";
    sql_SelectDevice  = "select * from device where station = :user_select";
    sql_UpdateCombox  = "";





}

QString global::returenComBoxCurrentText(QString currentComboboxSelect,int indexComboBox)
{
    QString test = (currentComboboxSelect);
    sql_PollingSelectDuan= QObject::tr("select duan from '");
    sql_PollingSelectJian =  QObject::tr("select jian from `check` where duan ='%1'").arg(test);
    sql_PollingSelectQu = QObject::tr ("select qu from `check` where jian='%1'").arg(test);
    sql_PollingSelectStation =  QObject::tr("select station from `check` where qu='%1'").arg(test);
    sql_PollingSelectDevice =  QObject::tr("select deviceid from `check`where station='%1'").arg(test);
    if(indexComboBox == 0)
         return sql_PollingSelectJian;
    else if(indexComboBox == 1)
         return sql_PollingSelectQu;
    else if(indexComboBox == 2)
         return sql_PollingSelectStation;
    else if(indexComboBox == 3)
         return sql_PollingSelectDevice;


}

bool global::logSelectFromUserModel(QString user)
{
    QString sql;
    QSqlQuery query;
    sql = QObject::tr("select userid,recorddate,operation from log where userid  = '%1'").arg(user);
    bool prepare_status = query.prepare(sql);
    if(!prepare_status)
        return ERROR_PREPARE_SQL_LOG_GLOBAL;
//    bool exec_status = query.exec();
//    if(!exec_status)
//        return ERROR_EXEC_SQL_LOG_GLOBAL;

    queryUserModel = new QSqlQueryModel;
    queryUserModel->setQuery(query);
}


QString global::log_SQL(int index)
{
    QString sql_LogSelectUseridForComboBox;
    if(index  ==  0)
    {
         sql_LogSelectUseridForComboBox = QString ::fromLocal8Bit("select userid from user");
    }
    return sql_LogSelectUseridForComboBox;
}

QString global::log_SQL_UseridModel_Select(QString string,int index)
{
    QString sql ;
    if(index == 0)
    {
        QString sql_SelectFromUserid;
        sql = QObject::tr("select userid,recorddate,operation from log where userid = '%1'").arg(string);
    }else if(index == 1)
    {
        sql = QObject::tr("select userid,recorddate,operation from log where opertype = '%1'").arg(string);
    }else if(index == 2 )
    {
        qDebug()<<"string"<<string;
        sql = QObject::tr("SELECT userid,recorddate,operation FROM LOG");
    }
    return sql;
}

QString global::log_SQL_UseridModel_Select(QString startTime,QString endTime)
{
    QString sql;
    sql = QObject::tr("SELECT userid,recorddate,operation FROM LOG WHERE RecordDate  BETWEEN '%1' AND '%2'").arg(startTime,endTime);
     return sql;
}


//void global::alterDeviceDialog_Sql()
//{

//}


QString global::addDevice_SQL_Select(QString *string,int index)
{
    if(index == 0)
    {
        return "select duan from duan ;";
    }else if(index == 1)
    {
        return QObject::tr("select jian from jian where duan = '%1'").arg(string[0]);
    }else if(index == 2)
    {
        return QObject::tr("select qu from  qu where duan = '%1' and jian = '%2'").arg(string[0],string[1]);
    }else if(index == 3)
    {
        return QObject::tr("select station from station where duan ='%1' and jian = '%2' and qu = '%3'").arg(string[0],string[1],string[2]);
    }else if(index == 4)
    {
        return QObject::tr("select deviceid from device where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4'").arg(string[0],string[1],string[2],string[3]);
    }
}

QString global::addDeviceToMysql(QString *string)
{
    return QObject::tr("INSERT INTO device(duan,jian,qu,station,deviceid,ip,`port`) VALUES('%1','%2','%3','%4','%5','%6','%7')").arg(string[0],string[1],string[2],string[3],string[4],string[5],string[6]);
}


QString global::alterDeviceToMysql(QString *string)
{
    return QObject::tr("UPDATE device SET PORT = '%7', ip = '%6' WHERE duan = '%1' AND qu = '%2' AND jian = '%3' AND station = '%4' and deviceid = '%5'").arg(string[0],string[1],string[2],string[3],string[4],string[5],string[6]);
}

QString global::delDeviceFromMysql(QString *string)
{
    return QObject::tr(" DELETE FROM device WHERE duan = '%1' AND jian = '%2' AND qu = '%3' AND station = '%4' AND deviceid = '%5'").arg(string[0],string[1],string[2],string[3],string[4]);
}



void global::setStyle(const QString &StyleName)
{
    QString AppPath = QCoreApplication::applicationDirPath();
    QString QssPath = AppPath + QString::fromLocal8Bit("/image/qss/%1.css").arg(StyleName);
    qDebug()<<QString::fromLocal8Bit("qss路径:")<<QssPath;
    QFile file(QssPath);
    int status = file.open(QFile::ReadOnly);
    qDebug()<<"status"<<status;
    QString qss = QLatin1String(file.readAll());


    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));

}


global::~global()
{}

/*
void MainWindow::delay(int second)
{

    QTime t;
    t.start();
    while(t.elapsed()<50*second)
    QCoreApplication::processEvents();
}
*/


void global::fromUserSqlClassForCheckDB()
{
    //TODO
    //restart mysql db;

    qDebug()<<QString::fromLocal8Bit("收到重启数据库信号");
//    checkDB();
}


//void global::checkDB(MysqlSupport &global)
//{
//    global.db;
//}


