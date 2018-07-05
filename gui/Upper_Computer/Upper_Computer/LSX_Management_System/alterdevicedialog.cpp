#include "alterdevicedialog.h"
#include "ui_alterdevicedialog.h"
#include <QDebug>
#include <QComboBox>


AlterDeviceDialog::AlterDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlterDeviceDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setWindowTitle(QString::fromLocal8Bit("修改设备"));
    ui->spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_3->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_4->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox->setRange(0,255);
    ui->spinBox_2->setRange(0,255);
    ui->spinBox_3->setRange(0,255);
    ui->spinBox_4->setRange(0,255);

    sqlGlobal = new global;
    query = new QSqlQuery;

}

AlterDeviceDialog::~AlterDeviceDialog()
{
    delete ui;
}


void AlterDeviceDialog::setCombobox(QString * comboboxString)
{

    ui->comboBox->addItem(comboboxString[0]);
    ui->comboBox_2->addItem(comboboxString[1]);
    ui->comboBox_3->addItem(comboboxString[2]);
    ui->comboBox_4->addItem(comboboxString[3]);
    ui->comboBox_5->addItem(comboboxString[4]);

    ui->comboBox->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->comboBox_3->setEnabled(false);
    ui->comboBox_4->setEnabled(false);
    ui->comboBox_5->setEnabled(false);




    qDebug()<<"comboboxString[0]"<<comboboxString[0];
    qDebug()<<"comboboxString[0]"<<comboboxString[1];
    qDebug()<<"comboboxString[0]"<<comboboxString[2];
    qDebug()<<"comboboxString[0]"<<comboboxString[3];

}







void AlterDeviceDialog::on_pushButton_clicked()
{
    QString whereText[7];
    whereText[0] = ui->comboBox->currentText();
    whereText[1] = ui->comboBox_2->currentText();
    whereText[2] = ui->comboBox_3->currentText();
    whereText[3] = ui->comboBox_4->currentText();
    whereText[4] = ui->comboBox_5->currentText();
    whereText[5] = ui->spinBox->text()+"."+ui->spinBox_2->text()+"."+ui->spinBox_3->text()+"."+ui->spinBox_4->text();
    whereText[6] = ui->lineEdit->text();

    QString sql = QString::fromLocal8Bit("UPDATE device SET ip = '%1',`port` = '%2' WHERE duan = '%3' AND jian = '%4' AND qu = '%5' AND station = '%6' AND deviceid = '%7'").arg(whereText[5],whereText[6],whereText[0],whereText[1],whereText[2],whereText[3],whereText[4]);
    qDebug()<<"执行sql:"<<sql;


    QSqlQuery query;
    query.prepare(sql);
    if(query.exec())
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("修改成功!"),"prompt");
        box.exec();
    }
//    messageWarring(QString::fromLocal8Bit("修改成功"));
    this->close();
}


void AlterDeviceDialog::messageWarring(QString message)
{
    QMessageBox *box = new QMessageBox;
    box->setText(message);
    box->exec();
}

void AlterDeviceDialog::on_pushButton_2_clicked()
{
    this->close();
}
