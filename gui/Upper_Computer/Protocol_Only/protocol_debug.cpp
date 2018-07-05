#include "protocol_debug.h"
#include "ui_protocol_debug.h"

#include <QString>
#include <QCryptographicHash>


Protocol_Debug::Protocol_Debug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Protocol_Debug)
{
    ui->setupUi(this);
    connectIp = "192.168.6.52";
    connectPort = 8888;
    this->setWindowTitle("Debug:127.0.0.1");

    msg =  new ProtocolMessage;
    connect(msg,&ProtocolMessage::toMainShowMD5,this,&Protocol_Debug::showMD5);



    socket = new QTcpSocket;
    msg->setSocket(this->socket);
    qDebug()<<"socket addr:"<<socket;





}

Protocol_Debug::~Protocol_Debug()
{
    delete ui;
}

void Protocol_Debug::showMD5(QString s_MD5, int index)
{
    switch(index)
    {
    case 801:
        ui->textEdit->append(QString::fromLocal8Bit("801使用下位机生成标准MD5:"));
        break;
    case 800:
        ui->textEdit->append(QString::fromLocal8Bit("记录仪反馈标准MD5:"));
        break;
    case 001:
        ui->textEdit->append(QString::fromLocal8Bit("下位机明文:"));
        break;
    case 002:
        ui->textEdit->append(QString::fromLocal8Bit("上位机验证MD5:"));
    }

    qDebug()<<"s_MD5:"<<s_MD5;
    ui->textEdit->append(s_MD5);
}


//800
void Protocol_Debug::on_pushButton_clicked()
{
    socket->write(msg->M_800C);
    qDebug()<<"MMMM"<<msg->M_800C;
    ui->textEdit->setText("What fuck");
    ui->textEdit->append((msg->M_800C).toHex());
}

//801
void Protocol_Debug::on_pushButton_4_clicked()
{
    socket->write(msg->M_801C);
    ui->textEdit->append((msg->M_801C).toHex());

}

//802
void Protocol_Debug::on_pushButton_2_clicked()
{
    socket->write(msg->M_802C);
    ui->textEdit->append(msg->M_802C.toHex());
}

//804
void Protocol_Debug::on_pushButton_3_clicked()
{
    socket->write(msg->M_804C);
    ui->textEdit->append(msg->M_804C.toHex());
}


//808
void Protocol_Debug::on_pushButton_5_clicked()
{
    socket->write(msg->M_808C);
    ui->textEdit->append(msg->M_808C.toHex());
}


//809
void Protocol_Debug::on_pushButton_6_clicked()
{
    socket->write(msg->M_809C);
    ui->textEdit->append(msg->M_809C.toHex());
}

void Protocol_Debug::on_pushButton_7_clicked()
{

    socket->connectToHost(QHostAddress(connectIp),connectPort);//连接目标设备
    connect(socket,SIGNAL(readyRead()),msg,SLOT(my_Receive()));//协议中接受
}


void Protocol_Debug::on_pushButton_10_clicked()
{
    netSet = new Net_Set;
    connect(netSet,&Net_Set::toMainNetSet,this,&Protocol_Debug::setNet);
    connect(netSet,&Net_Set::delNetSetObj,this,&Protocol_Debug::delNetSetObj);
    netSet->exec();
}

void Protocol_Debug::setNet(QString ip,int port)
{
    connectIp = ip;
    connectPort = port;
    ui->pushButton_7->setText(QString::fromLocal8Bit("连接") + connectIp + ":" + QString::number(connectPort));

}

void Protocol_Debug::on_pushButton_8_clicked()
{
    this->socket->disconnectFromHost();
}
