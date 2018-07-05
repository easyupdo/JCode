#include "net_set.h"
#include "ui_net_set.h"
#include <QDebug>

Net_Set::Net_Set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Net_Set)
{
    ui->setupUi(this);
    this->setWindowTitle("Net Set");

}

Net_Set::~Net_Set()
{
    delete ui;
}

void Net_Set::on_pushButton_clicked()
{
    QString ip = ui->lineEdit->text() + "." + ui->lineEdit_2->text() + "." + ui->lineEdit_3->text() + "." + ui->lineEdit_4->text();
    int port = ui->lineEdit_5->text().toInt();
    qDebug()<<"ip"<<ip<<"Port"<<port;
    emit toMainNetSet(ip,port);
    emit delNetSetObj();

}


void Net_Set::on_pushButton_2_clicked()
{
     emit delNetSetObj();
}



