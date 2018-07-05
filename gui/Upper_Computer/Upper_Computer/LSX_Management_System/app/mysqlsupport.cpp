#include "mysqlsupport.h"
#include <QMessageBox>
#include <QApplication>
#include <QSettings>


MysqlSupport::MysqlSupport(QObject *parent) : QObject(parent)
{
    mysqlConfig();
    mysqlConnect();

}

void MysqlSupport::mysqlConnect()
{
    //mysql数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dbInfo.hostName);
    db.setUserName(dbInfo.userName);
    db.setPassword(dbInfo.passWord);
    db.setDatabaseName(dbInfo.databaseName);
    db.setConnectOptions("MYSQL_OPT_RECONNECT=1");

    global log;

    if(db.open())
         {
             qDebug() << "database is established!";
             //sqlModel = new QSqlQueryModel();
//             sqlModel->setQuery(QString("select * from user"));
          //   ui->tableView->setModel(model);
            // model->setHeaderData(0, Qt::Horizontal, tr("name"));
           //  int x = ui->tableView->currentIndex().row();//当前用户点击tableview的行号
           //  int y = ui->tableView->currentIndex().column();//当前用户点击tableview的行号
            //  qDebug() <<x <<y;
            //   int i= 0;
            //  QModelIndex indextemp = model->index(0,0);//第i行第一列的值
            //  QString string = indextemp.data().toString();

         //     qDebug() <<"TT"<<string;
         }
         else
         {

             qDebug() << "build error!";
             QStringList driverList = QSqlDatabase::drivers();
             qDebug()<<QString::fromLocal8Bit("可用驱动:")<<driverList;
             QMessageBox *dbInfomation = new QMessageBox();
             dbInfomation->setText(QString::fromLocal8Bit("数据库打开错误,请检查数据库连接"));
             int status = dbInfomation->exec();
             if(status == QMessageBox::Ok)
             {
                qApp->closeAllWindows();
             }
           //  return false;
         }
}

void MysqlSupport::fromMainWindow()//收到该信号 表示数据库连接有问题 需要检查
{
    qDebug()<<QString::fromLocal8Bit("信号来自DeviceControl->MainWindow->LoginDialog!");
    if(!this->db.isOpen())//如果数据库没有连接  重新连接
    {
        mysqlReConnect();
    }

}

void MysqlSupport::mysqlReConnect()
{
        mysqlConnect();
}

void MysqlSupport::mysqlConfig()
{
    QString AppPath = QCoreApplication::applicationDirPath();
    qDebug()<<AppPath;
    QString mysqlIniFile = AppPath + "/config" + "/mysql.ini";
    QSettings settings(mysqlIniFile,QSettings::IniFormat);
    settings.beginGroup("Mysql");
    dbInfo.hostName = settings.value("HosetName").toString();//localhost
    dbInfo.userName = settings.value("UserName").toString();//root
    dbInfo.passWord = settings.value("Password").toString();//123456
    dbInfo.databaseName = settings.value("DatabaseName").toString();//hm
    settings.endGroup();

    qDebug()<<QString::fromLocal8Bit("数据库:")<<dbInfo.hostName<<dbInfo.userName<<dbInfo.passWord<<dbInfo.databaseName;
}


