#include "addoralterjiandialog.h"
#include "ui_addoralterjiandialog.h"
#include  <QDebug>

addOrAlterJianDialog::addOrAlterJianDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addOrAlterJianDialog)
{
    ui->setupUi(this);
     alterNoSelectFlag = false;
     this->setWindowFlags(Qt::FramelessWindowHint);
}

addOrAlterJianDialog::~addOrAlterJianDialog()
{
    delete ui;
}


void addOrAlterJianDialog::fromDeviceManagementFormForAlterJian(bool status, QString stringMsg[])
{
    alterNoSelectFlag = status;
    qDebug()<<"stringQQQQQQQQ::"<<stringMsg[0];
    qDebug()<<"stringQQQQQQQQ::"<<stringMsg[1];
    qDebug()<<"stringQQQQQQQQ::"<<stringMsg[2];

    if(alterNoSelectFlag)//修改
    {
        ui->comboBox->setEnabled(false);
         ui->lineEdit_2->setEnabled(false);
        ui->comboBox->clear();
        ui->comboBox->addItem(stringMsg[0]);
        ui->addDuan_Title->setText(QString::fromLocal8Bit("修改电间"));
        ui->lineEdit_2->setText(stringMsg[1]);
        ui->lineEdit_3->setText(stringMsg[4]);
        ui->lineEdit_4->setText(stringMsg[5]);
    }else
    {
        ui->comboBox->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        setComboBox();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
    }
}

void addOrAlterJianDialog::on_addDuan_CloseButton_clicked()
{
    this->close();
}


void addOrAlterJianDialog::Jian()
{
    iMessageBox box;
    QSqlQuery query;
    if(alterNoSelectFlag)//修改
    {

        QString duan_Update_SQL= QObject::tr("update jian set telephone ='%1',contact = '%2' where jian = '%3'").arg(ui->lineEdit_4->text(),ui->lineEdit_3->text(),ui->lineEdit_2->text());
        query.prepare(duan_Update_SQL);
        if(query.exec())
        {
            box.setMessageType("prompt");
            box.setMessageText(QString::fromLocal8Bit("修改成功!"));
            box.exec();
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
        if(ui->lineEdit_2->text() == "")
        {
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("电间不能为空!"));
            box.exec();
        }else
        {
            QString sql = QString::fromLocal8Bit("select jian from jian where jian = '%1'").arg(ui->lineEdit_2->text());
            query.prepare(sql);
            query.exec();
            if(query.next())
            {
                qDebug()<<QString::fromLocal8Bit("查询到:")<<query.value(0).toString();
                box.setMessageType("error");
                box.setMessageText(QString::fromLocal8Bit("电间名字已经存在,请使用其他名字!"));
                box.exec();
            }else
            {
                QString insertSQL = QObject::tr("insert into jian(duan,jian,telephone,contact) values('%1','%2','%3','%4')").arg(ui->comboBox->currentText(),ui->lineEdit_2->text(),ui->lineEdit_4->text(),ui->lineEdit_3->text());
                query.prepare(insertSQL);
                qDebug()<<QString::fromLocal8Bit("插入SQL:")<<insertSQL;
    //            qDebug()<<QString::fromLocal8Bit("sql执行状态:")<<;
                if(query.exec())
                {
                    qDebug()<<QString::fromLocal8Bit("插入成功");
                    box.setMessageType("prompt");
                    box.setMessageText(QString::fromLocal8Bit("添加成功!"));
                    box.exec();
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


void addOrAlterJianDialog::on_pushButton_clicked()
{
    Jian();
    emit toDeviceManagementForUpdateTableview_2_Show("jian");
}

void addOrAlterJianDialog::setComboBox()
{
    ui->comboBox->clear();
    QSqlQuery query;
    query.exec("select duan from duan");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }
}

void addOrAlterJianDialog::on_pushButton_2_clicked()
{
    this->close();
}
