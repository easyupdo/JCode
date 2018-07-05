#include "addquoralterdialog.h"
#include "ui_addquoralterdialog.h"
#include  <QDebug>

addQuOrAlterDialog::addQuOrAlterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addQuOrAlterDialog)
{
    ui->setupUi(this);
    alterNoSelectFlag = false;
    this->setWindowFlags(Qt::FramelessWindowHint);
    mousePressed = false;
//    setComboBox_duan();
}

addQuOrAlterDialog::~addQuOrAlterDialog()
{
    delete ui;
}


void addQuOrAlterDialog::fromDeviceManagementFormForAlterQu(bool status, QString stringMsg[])
{
    alterNoSelectFlag = status;
    qDebug()<<"Status:"<<status<<alterNoSelectFlag;
    if(alterNoSelectFlag)//1:修改
    {
        ui->addDuan_Title->setText(QString::fromLocal8Bit("修改工区"));
        ui->comboBox->clear();
        ui->comboBox->addItem(stringMsg[0]);
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem(stringMsg[1]);
        qDebug()<<"STRing:"<<stringMsg[0]<<stringMsg[1]<<stringMsg[2];
        ui->lineEdit_2->setText(stringMsg[2]);
        ui->lineEdit_3->setText(stringMsg[4]);
        ui->lineEdit_4->setText(stringMsg[5]);
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);

    }else
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        setComboBox_duan();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();

    }
}



void addQuOrAlterDialog::setComboBox_duan()
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

void addQuOrAlterDialog::setComboBox_jian(QString duan)
{
    ui->comboBox_2->clear();
    QSqlQuery query;
    query.exec(QString::fromLocal8Bit("select jian from jian where duan = '%1'").arg(duan));
    while(query.next())
    {
        ui->comboBox_2->addItem(query.value(0).toString());
    }
}


void addQuOrAlterDialog::on_comboBox_activated(const QString &arg1)
{
    setComboBox_jian(arg1);
}


void addQuOrAlterDialog::Qu()
{
    iMessageBox box;
    QSqlQuery query;
    if(alterNoSelectFlag)//修改
    {
        ui->lineEdit_2->setEnabled(false);
        QString duan_Update_SQL= QObject::tr("update qu set telephone ='%1',contact = '%2' where qu = '%3'").arg(ui->lineEdit_4->text(),ui->lineEdit_3->text(),ui->lineEdit_2->text());
        query.prepare(duan_Update_SQL);
        qDebug()<<QString::fromLocal8Bit("QSL:")<<duan_Update_SQL;
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
        if(ui->lineEdit_2->text() == "")
        {
            box.setMessageType("error");
            box.setMessageText(QString::fromLocal8Bit("工区不能为空!"));
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
                box.setMessageText(QString::fromLocal8Bit("工区名字已经存在,请使用其他名字!"));
                box.exec();
            }else
            {
                QString insertSQL = QObject::tr("insert into qu(duan,jian,qu,telephone,contact) values('%1','%2','%3','%4','%5')").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->lineEdit_2->text(),ui->lineEdit_4->text(),ui->lineEdit_3->text());
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

void addQuOrAlterDialog::on_pushButton_clicked()
{
    Qu();
    emit toDeviceManagementForUpdateTableview_2_Show("qu");
}

void addQuOrAlterDialog::on_pushButton_2_clicked()
{
    this->close();
}

void addQuOrAlterDialog::on_addDuan_CloseButton_clicked()
{
    this->close();
}


void addQuOrAlterDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void addQuOrAlterDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void addQuOrAlterDialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
