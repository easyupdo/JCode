#include "addduan_dialog.h"
#include "ui_addduan_dialog.h"
#include <QDebug>
#include <QSqlQuery>

addDuan_Dialog::addDuan_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDuan_Dialog)
{
    ui->setupUi(this);
    this->mousePressed = false;
    this->setWindowFlags(Qt::FramelessWindowHint);
    alterNoSelectFlag = false;
}

addDuan_Dialog::~addDuan_Dialog()
{
    delete ui;
}

void addDuan_Dialog::on_pushButton_clicked()
{
    addDuan();
}

void addDuan_Dialog::fromDeviceManagementFormForJudgeAddOrAlter(bool status,QString stringMsg[])
{
    alterNoSelectFlag = status;
    qDebug()<<"stringQQQQQQQQ::"<<stringMsg[0];
    qDebug()<<"stringQQQQQQQQ::"<<stringMsg[1];
    qDebug()<<"stringQQQQQQQQ::"<<stringMsg[2];
    ui->lineEdit->setText(stringMsg[0]);
    ui->lineEdit_2->setText(stringMsg[4]);
    ui->lineEdit_3->setText(stringMsg[5]);
    if(alterNoSelectFlag)//修改
    {
        ui->lineEdit->setEnabled(false);
        ui->addDuan_Title->setText(QString::fromLocal8Bit("修改电段"));
//        ui->lineEdit->setText("hello sb");
    }
}

void addDuan_Dialog::addDuan()
{
    iMessageBox box;
    QSqlQuery query;
    if(alterNoSelectFlag)//修改
    {

        QString duan_Update_SQL= QObject::tr("update duan set telephone ='%1',contact = '%2' where duan = '%3'").arg(ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit->text());
        query.prepare(duan_Update_SQL);
        if(query.exec())
        {
            box.setMessageType("prompt");
            box.setMessageText(QString::fromLocal8Bit("修改成功!"));
            box.exec();
            emit toDeviceManagementForUpdateTableview_2_Show("duan");
            this->close();
        }
        else
        {
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("修改失败!"));
            box.exec();
            this->close();
        }
    }else//add
    {
        //clear all lineEdit
        if(ui->lineEdit->text() == "")
        {
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("电段不能为空!"));
            box.exec();
        }else
        {
            QString sql = QString::fromLocal8Bit("select duan from duan where duan = '%1'").arg(ui->lineEdit->text());
            query.prepare(sql);
            query.exec();
            if(query.next())
            {
                qDebug()<<QString::fromLocal8Bit("查询到:")<<query.value(0).toString();
                box.setMessageType("error");
                box.setMessageText(QString::fromLocal8Bit("电段名字已经存在,请使用其他名字!"));
                box.exec();
            }else
            {
                QString insertSQL = QObject::tr("insert into duan(duan,telephone,contact) values('%1','%2','%3')").arg(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text());
                query.prepare(insertSQL);
                qDebug()<<QString::fromLocal8Bit("插入SQL:")<<insertSQL;
    //            qDebug()<<QString::fromLocal8Bit("sql执行状态:")<<;
                if(query.exec())
                {
                    qDebug()<<QString::fromLocal8Bit("插入成功");
                    box.setMessageType("prompt");
                    box.setMessageText(QString::fromLocal8Bit("添加成功!"));
                    box.exec();
                    emit toDeviceManagementForUpdateTableview_2_Show("duan");
                    this->close();
                }else
                 {
                    box.setMessageType("error");
                    box.setMessageText(QString::fromLocal8Bit("添加失败!"));
                    box.exec();
                    this->close();
                 }
            }
        }
    }



}

void addDuan_Dialog::on_addDuan_CloseButton_clicked()
{
    this->close();
}

void addDuan_Dialog::on_pushButton_2_clicked()
{
    this->close();
}


void addDuan_Dialog::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void addDuan_Dialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void addDuan_Dialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
