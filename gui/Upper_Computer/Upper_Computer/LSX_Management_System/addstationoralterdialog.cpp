#include "addstationoralterdialog.h"
#include "ui_addstationoralterdialog.h"
#include <QDebug>

addStationOrAlterDialog::addStationOrAlterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStationOrAlterDialog)
{
    ui->setupUi(this);
    alterNoSelectFlag = false;
    mousePressed = false;
    this->setWindowFlags(Qt::FramelessWindowHint);
}

addStationOrAlterDialog::~addStationOrAlterDialog()
{
    delete ui;
}

void addStationOrAlterDialog::fromDeviceManagementFormForAlterStation(bool status, QString stringMsg[])
{
    alterNoSelectFlag = status;
    qDebug()<<"Status:"<<status<<alterNoSelectFlag;
    if(alterNoSelectFlag)//1:修改
    {
        ui->addDuan_Title->setText(QString::fromLocal8Bit("修改车间"));
        ui->comboBox->clear();
        ui->comboBox->addItem(stringMsg[0]);
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem(stringMsg[1]);
        ui->comboBox_3->clear();
        ui->comboBox_3->addItem(stringMsg[2]);
        ui->lineEdit_3->setText(stringMsg[3]);
        ui->lineEdit_4->setText(stringMsg[4]);
        ui->lineEdit_5->setText(stringMsg[5]);
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->lineEdit_3->setEnabled(false);

    }else
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        setComboBox_duan();

    }
}


void addStationOrAlterDialog::setComboBox_duan()
{
    ui->comboBox->clear();
    QSqlQuery query;
    query.exec("select duan from duan");
    while(query.next())
    {
        qDebug()<<QString::fromLocal8Bit("工区添加段:")<<query.value(0).toString();
        ui->comboBox->addItem(query.value(0).toString());
    }
}

void addStationOrAlterDialog::setComboBox_jian(QString duan)
{
    ui->comboBox_2->clear();
    QSqlQuery query;
    query.exec(QString::fromLocal8Bit("select jian from jian where duan = '%1'").arg(duan));
    while(query.next())
    {
        ui->comboBox_2->addItem(query.value(0).toString());
    }
}

void addStationOrAlterDialog::on_comboBox_activated(const QString &arg1)
{
    setComboBox_jian(arg1);
    setComboBox_qu(ui->comboBox_2->currentText());
}

void addStationOrAlterDialog::setComboBox_qu(QString jian)
{
    ui->comboBox_3->clear();
    QSqlQuery query;
    query.exec(QString::fromLocal8Bit("select qu from qu where duan = '%1' and jian = '%2'").arg(ui->comboBox->currentText(),jian));
    while(query.next())
    {
        ui->comboBox_3->addItem(query.value(0).toString());
    }
}

void addStationOrAlterDialog::on_comboBox_2_activated(const QString &arg1)
{
    setComboBox_qu(arg1);
}

void addStationOrAlterDialog::on_pushButton_clicked()
{
    Station();
    emit toDeviceManagementForUpdateTableview_2_Show("station");
}

void addStationOrAlterDialog::Station()
{
    iMessageBox box;
    QSqlQuery query;
    if(alterNoSelectFlag)//修改
    {

        QString duan_Update_SQL= QObject::tr("update station set telephone ='%1',contact = '%2' where station = '%3'").arg(ui->lineEdit_5->text(),ui->lineEdit_4->text(),ui->lineEdit_3->text());
        query.prepare(duan_Update_SQL);
        qDebug()<<QString::fromLocal8Bit("updat修改:")<<duan_Update_SQL;
        if(query.exec())
        {
            box.setMessageType("prompt");
            box.setMessageText(QString::fromLocal8Bit("修改成功!"));
            box.exec();
            emit toDeviceManagementForUpdateTableview_2_Show("jian");
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
        if(ui->lineEdit_3->text() == "")
        {
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("车站不能为空!"));
            box.exec();
        }else
        {
            QString sql = QString::fromLocal8Bit("select jian from jian where jian = '%1'").arg(ui->lineEdit_3->text());
            query.prepare(sql);
            query.exec();
            if(query.next())
            {
                qDebug()<<QString::fromLocal8Bit("查询到:")<<query.value(0).toString();
                box.setMessageType("error");
                box.setMessageText(QString::fromLocal8Bit("车站名字已经存在,请使用其他名字!"));
                box.exec();
            }else
            {
                QString insertSQL = QObject::tr("insert into station(duan,jian,qu,station,telephone,contact) values('%1','%2','%3','%4','%5','%6')").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->lineEdit_3->text(),ui->lineEdit_5->text(),ui->lineEdit_4->text());
                query.prepare(insertSQL);
                qDebug()<<QString::fromLocal8Bit("插入SQL:")<<insertSQL;
    //            qDebug()<<QString::fromLocal8Bit("sql执行状态:")<<;
                if(query.exec())
                {
                    qDebug()<<QString::fromLocal8Bit("插入成功");
                    box.setMessageType("prompt");
                    box.setMessageText(QString::fromLocal8Bit("添加成功!"));
                    box.exec();
                    emit toDeviceManagementForUpdateTableview_2_Show("jian");
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

void addStationOrAlterDialog::on_pushButton_2_clicked()
{
    this->close();
}

void addStationOrAlterDialog::on_addDuan_CloseButton_clicked()
{
    this->close();
}


void addStationOrAlterDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void addStationOrAlterDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void addStationOrAlterDialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
