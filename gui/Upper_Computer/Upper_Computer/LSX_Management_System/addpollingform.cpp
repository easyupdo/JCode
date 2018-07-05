#include "addpollingform.h"
#include "ui_addpollingform.h"

#include <ui_devicepollingform.h>
#include <QDebug>
#include <QTimer>
#include <QDate>
#include <QSqlQuery>
#include "adduserform.h"
#include <QMessageBox>



addPollingForm::addPollingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addPollingForm)
{

    ui->setupUi(this);
    checkNetFlag = false;
    checkVoiceFlag =false;
    this->mousePressed = false;
    this->setWindowTitle(QString::fromLocal8Bit("添加巡检设备"));
    setWindowFlags(Qt::FramelessWindowHint);
//    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::ApplicationModal );



}

addPollingForm::~addPollingForm()
{
    delete ui;
}

void addPollingForm::fromPollingDevice(QString string[])//接受主界面的信号
{
    qDebug()<<"sss"<<string[0];
    qDebug()<<"sss"<<string[1];
    qDebug()<<"sss"<<string[2];
    qDebug()<<"sss"<<string[3];
    qDebug()<<"sss"<<string[4];

    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    checkNetFlag = false;
    checkVoiceFlag =false;

    ui->comboBox_6->setCurrentText("8");
    ui->comboBox_7->setCurrentText("8");

    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();

    ui->comboBox->addItem(string[0]);
    ui->comboBox_4->addItem(string[1]);
    ui->comboBox_2->addItem(string[2]);
    ui->comboBox_5->addItem(string[3]);
    ui->comboBox_3->addItem(string[4]);

    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
    ui->comboBox_4->setEnabled(false);
    ui->comboBox_5->setEnabled(false);
    showCurrentTime();

}


void addPollingForm::showCurrentTime()
{
    QTime  *time = new QTime;
    ui->timeEdit->setTime(time->currentTime());
    ui->timeEdit_2->setTime(time->currentTime());
    qDebug()<<"NowTime:"<<time->currentTime();
}

/*
 *   sql = QString::fromLocal8Bit("select duan from duan");
        QSqlQuery query;
        query.prepare(sql);
        query.exec();
        while(query.next())
        {
            insertDuanQstring.append(query.value(0).toString());
        }
        qDebug()<<"insertDuanQstringSize:"<<insertDuanQstring.size();
        int duanAccount = insertDuanQstring.size();

        for(int i = 0;i<duanAccount;i++)
        {
            sql = QString::fromLocal8Bit("select jian from jian where duan = '%1'").arg(insertDuanQstring.at(i));
            query.prepare(sql);
            query.exec();
            while(query.next())
            {
                insertJianQstring.append(query.value(0).toString());
            }
        }
        qDebug()<<"2222222:"<<insertJianQstring.size();

*/
//判断添加到数据库多少条
QString addPollingForm::readyAddDateSql()
{
    QString sql;
    QList<QString>insertDuanQstring;
    QList<QString>insertJianQstring;
    if(ui->comboBox->currentText() == QString::fromLocal8Bit("*全部*"))
    {
        sql = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid from device ");
    }else if(ui->comboBox_4->currentText() == QString::fromLocal8Bit("*全部*"))
    {
        sql = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid from device where duan = '%1'").arg(ui->comboBox->currentText());
    }else if(ui->comboBox_2->currentText() == QString::fromLocal8Bit("*全部*"))
    {
        sql  = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid from device where duan  = '%1' and jian = '%2'").arg(ui->comboBox->currentText(),ui->comboBox_4->currentText());
    }else if(ui->comboBox_5->currentText() == QString::fromLocal8Bit("*全部*"))
    {
        sql = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid from device where duan  = '%1' and jian = '%2' and qu = '%3'").arg(ui->comboBox->currentText(),ui->comboBox_4->currentText(),ui->comboBox_2->currentText());
    }else if(ui->comboBox_3->currentText() == QString::fromLocal8Bit("*全部*"))
    {
        sql = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid from device where duan  = '%1' and jian = '%2' and qu = '%3' and station = '%4'").arg(ui->comboBox->currentText(),ui->comboBox_4->currentText(),ui->comboBox_2->currentText(),ui->comboBox_5->currentText());
    }
    else
    {
        sql = QString::fromLocal8Bit("select duan,jian,qu,station,deviceid from device where duan  = '%1' and jian = '%2' and qu = '%3' and station = '%4' and deviceid = '%5'").arg(ui->comboBox->currentText(),ui->comboBox_4->currentText(),ui->comboBox_2->currentText(),ui->comboBox_5->currentText(),ui->comboBox_3->currentText());
    }
return sql;
}


//添加到数据库
void addPollingForm::addToMysql()
{
    QList<QString> insertReadyList;
    QString sql = readyAddDateSql();
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
    while(query.next())
    {
        QString oneString  = query.value(0).toString();
        qDebug()<<"1String:"<<oneString;
        insertReadyList.append(oneString);
        insertReadyList.append(query.value(1).toString());
        insertReadyList.append(query.value(2).toString());
        insertReadyList.append(query.value(3).toString());
        insertReadyList.append(query.value(4).toString());
    }
    int insertNumber = insertReadyList.size()/5;//搜索所有要添加到数据库的条数
    qDebug()<<"Size:"<<insertNumber;
    QDate date = QDate::currentDate();

    QString checkNetString = QString::fromLocal8Bit("网络连接");
    QString checkVoiceString = QString::fromLocal8Bit("语音记录");
    QString checkstate = "2";//巡检状态       后要结合网络控制变量
    QString errorcount = "0";//巡检错误代码
    QString toSqlStartTime  =  date.toString("yyyy-MM-dd ") +ui->timeEdit->text();
    qDebug()<<"toSqlStartTime"<<toSqlStartTime;

 int insertCount = 0;
for(int i = 0;i<insertNumber;i++)
{
    QString devicePosition = QObject::tr("'%1','%2','%3','%4','%5',").arg(insertReadyList.at(0+i*5),insertReadyList.at(1+i*5),insertReadyList.at(2+i*5),insertReadyList.at(3+i*5),insertReadyList.at(4+i*5));
    QString deviceNetState = QObject::tr("'%1','%2','%3','%4','%5','%6'").arg(toSqlStartTime,ui->comboBox_6->currentText(),checkNetString,checkstate,errorcount,toSqlStartTime);//从开始时间开始后的7个 LastCheckTime 与 StartTime相同
    QString deviceVoiceState = QObject::tr("'%1','%2','%3','%4','%5','%6'").arg(toSqlStartTime,ui->comboBox_7->currentText(),checkVoiceString,checkstate,errorcount,toSqlStartTime);//最后一个是下次执行时间，暂定为与开始时间相同
    //     qDebug()<<"devicePosition:"<<devicePosition;
    qDebug()<<"deviceNetState:"<<deviceNetState;
     qDebug()<<"deviceVoiceState:"<<deviceVoiceState;
    QString sqlNet = QString::fromLocal8Bit("INSERT INTO `check` (duan,jian,qu,station,deviceid,starttime,span,content,checkstate,errorcount,historytime) VALUES(") + devicePosition + deviceNetState + ")";
    QString sqlVoice = QString::fromLocal8Bit("INSERT INTO `check` (duan,jian,qu,station,deviceid,starttime,span,content,checkstate,errorcount,historytime) VALUES(") + devicePosition + deviceVoiceState + ")";

    QSqlQuery checkQuery;
    QString checkSqlNet = QObject::tr("select * from `check`where duan ='%1' and jian = '%2' and qu ='%3' and station = '%4' and deviceid = '%5' and content = '%6'").arg(insertReadyList.at(0+i*5),insertReadyList.at(1+i*5),insertReadyList.at(2+i*5),insertReadyList.at(3+i*5),insertReadyList.at(4+i*5),checkNetString);
    QString checkSqlVoice = QObject::tr("select * from `check`where duan ='%1' and jian = '%2' and qu ='%3' and station = '%4' and deviceid = '%5' and content = '%6'").arg(insertReadyList.at(0+i*5),insertReadyList.at(1+i*5),insertReadyList.at(2+i*5),insertReadyList.at(3+i*5),insertReadyList.at(4+i*5),checkVoiceString);

    qDebug()<<"insertNetSql:"<<sqlNet;
    qDebug()<<"insertVoiceSql:"<<sqlVoice;
    qDebug()<<"checkSql:"<<checkSqlNet;
    qDebug()<<"checkSql:"<<checkSqlVoice;

     if(checkNetFlag)//网络巡检
    {
         checkQuery.prepare(checkSqlNet);
         checkQuery.exec();//数据库已经存在 跳过
         if(checkQuery.next())
         {
             ;
         }else
         {
             query.prepare(sqlNet);
             if(query.exec())
                 insertCount +=1;
         }
    }
     if(checkVoiceFlag)//语音巡检
    {
         checkQuery.prepare(checkSqlVoice);
         checkQuery.exec();//数据库已经存在 跳过
         if(checkQuery.next())
         {
           ;
         }else
         {
             query.prepare(sqlVoice);
             if(query.exec())
                insertCount +=1;
         }

    }

    #ifdef UPDATE_DEBUG
        query.prepare("select duan,jian,qu,station from device");
        query.exec();
        while(query.next())
        {
        QSqlQuery iquery;
        QString s = QObject::tr("update device set deviceid = '0001' where duan = '%1' and jian = '%2' and qu='%3'").arg(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString());
        iquery.prepare(s);
        qDebug()<<s;
        iquery.exec();
    }
    #endif
    qDebug()<<"sqlNet:"<<sqlNet;
    qDebug()<<"sqlVoice"<<sqlVoice;
}
//插入完后反馈给用户插入了几条
qDebug()<<"insertCount "<<insertCount;
if(insertCount)
{
    QMessageBox * box = new QMessageBox;
    box->setText(QString::fromLocal8Bit("共添加%1条巡检").arg(QString::number(insertCount)));
    int status = box->exec();
    if(status == QMessageBox::Ok)
    {
        emit toDevicePolling_addOK();
        box->close();
    }
}else
{
    iMessageBox box;
    box.setMessageType("error");
    box.setMessageText(QString::fromLocal8Bit("共添加0条巡检信息!"));
    box.exec();
//         break;
}

}



void addPollingForm::on_checkBox_clicked()
{
    checkNetFlag =  !checkNetFlag;
}

void addPollingForm::on_checkBox_2_clicked()
{
    checkVoiceFlag = !checkVoiceFlag;
}

void addPollingForm::on_pushButton_clicked()
{
    addToMysql();
    this->close();
}

void addPollingForm::on_pushButton_2_clicked()
{
    this->close();
}



void addPollingForm::on_addPollingCloseButton_clicked()
{
    this->close();
}

void addPollingForm::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void addPollingForm::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void addPollingForm::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
