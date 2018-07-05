#include "alterpollingform.h"
#include "ui_alterpollingform.h"
#include <QDebug>

alterPollingForm::alterPollingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alterPollingForm)
{
    ui->setupUi(this);
    this->mousePressed = false;
    this->setWindowTitle(QString::fromLocal8Bit("修改巡检设备"));
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setComboBox_6AndSetComboBOx_7();
}

alterPollingForm::~alterPollingForm()
{
    delete ui;
}

void alterPollingForm::fromPollingDevice(QString * string)
{
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

    ui->checkBox->setEnabled(false);
    ui->checkBox_2->setEnabled(false);

    qDebug()<<"content:"<<string[5];
    qDebug()<<"starttimeXXX:"<<string[6];
    qDebug()<<"spanXXXX:"<<string[7];

    if(string[5] == QString::fromLocal8Bit("网络连接"))
    {
        QString str = string[6].right(8);  //string[6]从数据库中读出的全格式时间   YY-MM-DD hh-mm-ss  先截取掉 然后转QTime 给timeEdit
        QTime time = QTime::fromString(string[6]);
        qDebug()<<"str++++++++;"<<str;

        ui->timeEdit->setTime(QTime::fromString(str));//开始时间      网络
//        ui->comboBox_6->clear();
//        ui->comboBox_7->clear();

        qDebug()<<QString::fromLocal8Bit("时间间隔:")<<string[7];
        if(string[7]=="8")
        {
            qDebug()<<QString::fromLocal8Bit("0000:");
              ui->comboBox_6->itemText(0);//显示当前巡检间隔
        }else if(string[7] == "12")
        {
            qDebug()<<QString::fromLocal8Bit("1111:");
            ui->comboBox_6->itemText(1);//显示当前巡检间隔
        }else if(string[7] == "24")
        {
            qDebug()<<QString::fromLocal8Bit("2222:");
               ui->comboBox_6->itemText(2);//显示当前巡检间隔
        }

        ui->timeEdit_2->setTime(QTime::fromString("00:00:00"));

        ui->checkBox->setChecked(true);
        ui->timeEdit_2->setEnabled(false);
        ui->comboBox_7->setEnabled(false);

        ui->checkBox_2->setChecked(false);
        ui->timeEdit->setEnabled(true);
        ui->comboBox_6->setEnabled(true);



    }else if(string[5] == QString::fromLocal8Bit("语音记录"))
    {
        ui->timeEdit_2->setTime(QTime::fromString(string[6].right(8)));//开始时间      语音
        ui->timeEdit->setTime(QTime::fromString("00:00:00"));
//        ui->comboBox_7->clear();
//        ui->comboBox_6->clear();
        if(string[7]=="8")
        {
              ui->comboBox_7->itemText(0);//显示当前巡检间隔
        }else if(string[7] == "12")
        {
            ui->comboBox_7->itemText(1);//显示当前巡检间隔
        }else if(string[7] == "24")
        {
               ui->comboBox_7->itemText(2);//显示当前巡检间隔
        }

        ui->checkBox_2->setChecked(true);
        ui->timeEdit->setEnabled(false);
        ui->comboBox_6->setEnabled(false);

        ui->checkBox->setChecked(false);
        ui->timeEdit_2->setEnabled(true);
        ui->comboBox_7->setEnabled(true);
    }
}

void alterPollingForm::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void alterPollingForm::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void alterPollingForm::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

//修改取消
void alterPollingForm::on_pushButton_2_clicked()
{
    this->close();
    emit toDevicePollingForClearUserSelectConotrol();
}

//修改确认  跟新用户修改的内容
void alterPollingForm::on_pushButton_clicked()
{
    //UPDATE `check` SET StartTime = 0001 WHERE duan = "海拉尔" AND jian = "博克图通信" AND qu= "海拉尔" AND station = "博克图" AND deviceid = "0001"
   //QString toSqlStartTime  =  date.toString("yyyy-MM-dd ") +ui->timeEdit->text();
    //开始时间写数据库的时候要转一下格式 现在写不进去
    QString sql;
    if(ui->checkBox->isChecked())
    {
        sql = QString::fromLocal8Bit("update `check` set starttime = '%1',span = '%2' where duan = '%3' and jian = '%4' and qu = '%5' and station = '%6' and deviceid = '%7' and content = '%8'")
                .arg(ui->timeEdit->text(),ui->comboBox_6->currentText(),ui->comboBox->currentText(),ui->comboBox_4->currentText(),ui->comboBox_2->currentText(),ui->comboBox_5->currentText(),ui->comboBox_3->currentText(),QString::fromLocal8Bit("网络连接"));
    }else if(ui->checkBox_2->isChecked())
    {
        sql = QString::fromLocal8Bit("update `check` set starttime = '%1',span = '%2' where duan = '%3' and jian = '%4' and qu = '%5' and station = '%6' and deviceid = '%7' and content = '%8'")
                .arg(ui->timeEdit_2->text(),ui->comboBox_7->currentText(),ui->comboBox->currentText(),ui->comboBox_4->currentText(),ui->comboBox_2->currentText(),ui->comboBox_5->currentText(),ui->comboBox_3->currentText(),QString::fromLocal8Bit("语音记录"));
    }
    qDebug()<<"sql:"<<sql;
    QSqlQuery query;
    query.prepare(sql);
    iMessageBox box;
    switch(query.exec())
    {
    case true:
        box.setMessageType("prompt");
        box.setMessageText(QString::fromLocal8Bit("修改成功!"));
        box.exec();
        this->close();
        break;
    case false:
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("修改失败!"));
        box.exec();
        break;
    }
    emit toDevicePollingForClearUserSelectConotrol();//clear user select

    //TODO update 巡检内容
}

void alterPollingForm::setComboBox_6AndSetComboBOx_7()
{
    QList<QString>items;
    items<<QString::fromLocal8Bit("8")<<QString::fromLocal8Bit("12")<<QString::fromLocal8Bit("24");
    ui->comboBox_6->addItems(items);
    ui->comboBox_7->addItems(items);
}


void alterPollingForm::on_alterPollingCloseButton_clicked()
{
    this->close();
}
