#include "userlogform.h"
#include "ui_userlogform.h"
#include <QString>
#include<QObject>
#include <QSqlQuery>
#include <QDebug>
#include <app/global.h>
#include <QDateTime>
#include <QTime>
#include "app/qmsqlquerymodel.h"

userLogForm::userLogForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userLogForm)
{
    ui->setupUi(this);
    initUserSelect_ComboBox();
    initDefaultShow();
    searchControlFlag = 0;
    model = new QMSqlQueryModel;

    ui->tableView->setModel(model);

    ui->tableView->verticalScrollBar()->setEnabled(false);
    ui->tableView->verticalScrollBar()->setVisible(false);
    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    setInitStyle();



 //   this->show();
}

userLogForm::~userLogForm()
{
    delete ui;
}

void userLogForm::on_comboBox_currentTextChanged(const QString &arg1)
{
        initUserOperationSelect_comboBox();
}

void userLogForm::initUserSelect_ComboBox()
{
    QString sql_LogUserSelect;
    this->logGlobal = new global;
   // sql_LogUserSelect =  QObject::tr("select userid from user ");
   sql_LogUserSelect =  this->logGlobal->log_SQL(0);
    QSqlQuery query;
    query.prepare(sql_LogUserSelect);
    query.exec();
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
        qDebug()<<"query.value(0):"<<query.value(0).toString();
    }
}


void userLogForm::initUserOperationSelect_comboBox()
{

}

void userLogForm::on_comboBox_2_currentTextChanged(const QString &arg1)
{
}




//void userLogForm::initLogTime_combobox_2()
//{

//}

void userLogForm::on_comboBox_3_currentTextChanged(const QString &arg1)
{

    if(arg1 == QString::fromLocal8Bit("按用户名"))
    {
        ui->label->setEnabled(true);
        ui->comboBox->setEnabled(true);//用户名

        ui->label_2->setEnabled(false);
        ui->comboBox_2->setEnabled(false);//操作

        ui->label_4->setEnabled(false);
        ui->dateEdit->setEnabled(false);//开始时间
        ui->timeEdit->setEnabled(false);

        ui->label_5->setEnabled(false);
        ui->dateEdit_2->setEnabled(false);//结束时间
        ui->timeEdit_2->setEnabled(false);
        logGlobal->logSelectFromUserModel(ui->comboBox->currentText());

        searchControlFlag = 0;
    }
    else if(arg1 == QString::fromLocal8Bit("按操作方式"))
    {
        ui->label->setEnabled(false);
        ui->comboBox->setEnabled(false);//用户名

        ui->label_2->setEnabled(true);
        ui->comboBox_2->setEnabled(true);//操作

        ui->label_4->setEnabled(false);
        ui->dateEdit->setEnabled(false);//开始时间
        ui->timeEdit->setEnabled(false);

        ui->label_5->setEnabled(false);
        ui->dateEdit_2->setEnabled(false);//结束时间
        ui->timeEdit_2->setEnabled(false);

          searchControlFlag = 1;
    }else if(arg1 == QString::fromLocal8Bit("按时间段"))
    {
        ui->label->setEnabled(false);
        ui->comboBox->setEnabled(false);//用户名

        ui->label_2->setEnabled(false);
        ui->comboBox_2->setEnabled(false);//操作

        ui->label_4->setEnabled(true);
        ui->dateEdit->setEnabled(true);//开始时间

        ui->label_5->setEnabled(true);
        ui->dateEdit_2->setEnabled(true);//结束时间
        ui->dateEdit->setCalendarPopup(true);
        ui->dateEdit_2->setCalendarPopup(true);
          searchControlFlag = 2;
    }

   // ui->tableView->setModel( logGlobal->queryUserModel);
}

void userLogForm::initDefaultShow()
{
//combobox:
        ui->label->setEnabled(true);
        ui->comboBox->setEnabled(true);//用户名

        ui->label_2->setEnabled(false);
        ui->comboBox_2->setEnabled(false);//操作

        ui->label_4->setEnabled(false);
        ui->dateEdit->setEnabled(false);//开始时间
        ui->timeEdit->setEnabled(false);//开始时间

        ui->label_5->setEnabled(false);
        ui->dateEdit_2->setEnabled(false);//结束时间
        ui->timeEdit_2->setEnabled(false);//开始时间
//combobox_2:
        stringLogOperation[0] = QString::fromLocal8Bit("用户登录");
        stringLogOperation[1] = QString::fromLocal8Bit("网络连接");
        stringLogOperation[2] = QString::fromLocal8Bit("下载语音列表");
        stringLogOperation[3] = QString::fromLocal8Bit("下载语音记录");
        stringLogOperation[4] = QString::fromLocal8Bit("播放语音记录");
        stringLogOperation[5] = QString::fromLocal8Bit("检索语音记录");
        stringLogOperation[6] = QString::fromLocal8Bit("检索日志记录");
        stringLogOperation[7] = QString::fromLocal8Bit("巡检设备");
        stringLogOperation[8] = QString::fromLocal8Bit("巡检结果");
        stringLogOperation[9] = QString::fromLocal8Bit("添加新用户");
        stringLogOperation[10] = QString::fromLocal8Bit("添加新电务段");
        stringLogOperation[11] = QString::fromLocal8Bit("添加新车间");
        stringLogOperation[12] = QString::fromLocal8Bit("添加新工区");
        stringLogOperation[13] = QString::fromLocal8Bit("添加新车站");
        stringLogOperation[14] = QString::fromLocal8Bit("添加新设备");
        stringLogOperation[15] = QString::fromLocal8Bit("添加设备巡检");
        stringLogOperation[16] = QString::fromLocal8Bit("修改用户信息");
        stringLogOperation[17] = QString::fromLocal8Bit("修改电段信息");
        stringLogOperation[18] = QString::fromLocal8Bit("修改车间信息");
        stringLogOperation[19] = QString::fromLocal8Bit("修改工区信息");
        stringLogOperation[20] = QString::fromLocal8Bit("修改车站信息");
        stringLogOperation[21] = QString::fromLocal8Bit("修改设备信息");
        stringLogOperation[22] = QString::fromLocal8Bit("修改巡检信息");
        stringLogOperation[23] = QString::fromLocal8Bit("删除用户信息");
        stringLogOperation[24] = QString::fromLocal8Bit("删除电段信息");
        stringLogOperation[25] = QString::fromLocal8Bit("删除车间信息");
        stringLogOperation[26] = QString::fromLocal8Bit("删除工区信息");
        stringLogOperation[27] = QString::fromLocal8Bit("删除站点信息");
        stringLogOperation[28] = QString::fromLocal8Bit("删除设备信息");
        stringLogOperation[29] = QString::fromLocal8Bit("删除巡检信息");
        stringLogOperation[30] = QString::fromLocal8Bit("删除日记记录");
        stringLogOperation[31] = QString::fromLocal8Bit("删除语音记录");
        stringLogOperation[32] = QString::fromLocal8Bit("导入语音记录");
        stringLogOperation[33] = QString::fromLocal8Bit("导出语音记录");
}

//搜索当前最大页码
void userLogForm::on_pushButton_clicked()
{
//    QMSqlQueryModel * model = new QMSqlQueryModel;
     QString sql;
     int searchAccount = 0;
    if(this->searchControlFlag == 0) //按用户
        sql= this->logGlobal->log_SQL_UseridModel_Select(ui->comboBox->currentText(),0);
    else if(this->searchControlFlag == 1)//按照操作
    {
        int i =0;
        for(;i<34;i++)
        {
            if(this->stringLogOperation[i] == ui->comboBox_2->currentText())
                break;
        }
        qDebug()<<"i:"<<i;
        sql = this->logGlobal->log_SQL_UseridModel_Select(QString::number(i),1);
    }else if(this->searchControlFlag == 2)//按时间段
    {
        QDateTime startTime;
        QTime sT = ui->timeEdit->time();
        QDate sD = ui->dateEdit->date();
        int second = ui->timeEdit->time().secsTo(ui->timeEdit_2->time());


     //  qDebug()<<"startTime"<<startTime;
       qDebug()<<"sD:"<<sD;
        qDebug()<<"sT:"<<sT;
        qDebug()<<"second:"<<second;
        if(ui->dateEdit->dateTime().secsTo(ui->dateEdit_2->dateTime()) < 0 )//second级别 start > end error
        {
           QMessageBox * box  = new QMessageBox;
           box->setText(QString::fromLocal8Bit("结束时间小于起始时间 请重新选择！   "));
           box->exec();
       }else
       {
           QString startTime = ui->dateEdit->text() + " "+ui->timeEdit->text();
            QString endTime = ui->dateEdit_2->text()+" "+ui->timeEdit_2->text();
           sql = this->logGlobal->log_SQL_UseridModel_Select(startTime,endTime);
            qDebug()<<"sql:SQL:"<<sql;
       }
       qDebug()<<"时间差："<<ui->dateEdit->dateTime().secsTo(ui->dateEdit_2->dateTime());
    }

    model->setQuery(sql);
    setTableviewHeadview();
    qDebug()<<"sql:"<<sql;
     ui->tableView->setModel(model);

    ui->label_7->setText(QString::number(model->rowCount()));


    //最大页码
    qDebug()<<"verticalScrollBar"<<ui->tableView->verticalScrollBar()->maximum();
    int lPage = model->rowCount()/(ui->tableView->verticalHeader()->height()/30);
    qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
    ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));

    if(lPage+1 > 0)
        ui->lineEdit->setText(QString::number(1));
}


//显示全部
void userLogForm::on_pushButton_2_clicked()
{
//    QMSqlmodel * model = new QMSqlmodel;
    QString sql = this->logGlobal->log_SQL_UseridModel_Select(ui->comboBox->currentText(),2);
    model->setQuery(sql);
    setTableviewHeadview();
     ui->tableView->setModel(model);
     ui->tableView->update();
     ui->tableView->verticalScrollBar()->update();

    ui->tableView->setModel(model);
//    ui->tableView->setColumnWidth(1,100);

    //最大页码
    for(int i = 0;i<1000;i++)
    {
        qDebug()<<"dd";
    }
    qDebug()<<"verticalScrollBar:"<<ui->tableView->verticalScrollBar()->maximum()<<model->rowCount();

    int lPage = model->rowCount()/(ui->tableView->verticalHeader()->height()/30);
    qDebug()<<QString::fromLocal8Bit("全部最大页:")<<lPage;
    ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));

    if(lPage+1 > 0)
        ui->lineEdit->setText(QString::number(1));

}

void userLogForm::setInitStyle()
{
    qDebug()<<"setInitStyle";
//    QMSqlmodel * model = new QMSqlmodel;
    QString sql =  QObject::tr("select userid,recorddate,operation from log where userid = '%1'").arg("");
    model->setQuery(sql);
    setTableviewHeadview();
     ui->tableView->setModel(model);

//    ui->tableView->setModel(model);
}



//后一页
void userLogForm::on_pushButton_5_clicked()
{
        ui->tableView->verticalScrollBar()->setValue(ui->tableView->verticalScrollBar()->value() + ui->tableView->verticalHeader()->height()/30);
        QString string = ui->label_11->text().mid(1);
        int stringLength = string.length();
        QString pageNum = string.left(stringLength - 1);
        qDebug()<<QString::fromLocal8Bit("HHH")<<pageNum;
        qDebug()<<ui->lineEdit->text().toInt();

        if(ui->lineEdit->text().toInt() >= pageNum.toInt())
        {
            iMessageBox box;
            box.setUserMessage(QString::fromLocal8Bit("已经是最后一页了!"),"prompt");
            box.exec();
        }else
        ui->lineEdit->setText(QString::number(ui->lineEdit->text().toInt() + 1));

        //更新总页码
           int lPage = model->rowCount()/(ui->tableView->verticalHeader()->height()/30);

            qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
            ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));

}


//前一页
void userLogForm::on_pushButton_4_clicked()
{
    ui->tableView->verticalScrollBar()->setValue(ui->tableView->verticalScrollBar()->value() - ui->tableView->verticalHeader()->height()/30);

    if(ui->lineEdit->text().toInt() <= 1)
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("已经是第一页了!"),"prompt");
        box.exec();
    }else
    ui->lineEdit->setText(QString::number(ui->lineEdit->text().toInt() - 1));

    //更新总页码
       int lPage = model->rowCount()/(ui->tableView->verticalHeader()->height()/30);

        qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
        ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));
}


//跳转
void userLogForm::on_pushButton_7_clicked()
{

    int lPageNum = ui->lineEdit->text().toInt();
    qDebug()<<QString::fromLocal8Bit("跳转page")<<lPageNum;
    ui->tableView->verticalScrollBar()->setValue( ui->tableView->verticalHeader()->height()/30* lPageNum);
}


//首页
void userLogForm::on_pushButton_3_clicked()
{
    ui->tableView->verticalScrollBar()->setValue( 0);
    ui->lineEdit->setText("1");

    //更新总页码
       int lPage = model->rowCount()/(ui->tableView->verticalHeader()->height()/30);

        qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
        ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));
}


//尾页
void userLogForm::on_pushButton_6_clicked()
{
    //更新总页码
       int lPage = model->rowCount()/(ui->tableView->verticalHeader()->height()/30);
       ui->tableView->verticalScrollBar()->setValue( ui->tableView->verticalHeader()->height()/30* (lPage + 1));
       ui->lineEdit->setText(QString::number(lPage));

        qDebug()<<QString::fromLocal8Bit("最大页:")<<lPage + 1;
        ui->label_11->setText(QString::fromLocal8Bit("/") + QString::number(lPage) + QString::fromLocal8Bit("页"));
}


void userLogForm::setTableviewHeadview()
{
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("用户名"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("记录时间"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("操作内容"));

    model->insertColumn(3);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    model->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit(" "));

//    model->insertRow(3);

}



