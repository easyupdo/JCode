#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket;
    ui->label->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    connect_flag = false;
     ui->pushButton->setEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::my_Receive()
{
    QByteArray receive_data =  this->socket->readAll();
    ui->textEdit->append(receive_data);
    if(QString(receive_data) =="OK")
    {
        ui->textEdit->append(QString::fromLocal8Bit("测评结束"));
        ui->pushButton->setEnabled(true);

    }
}

void MainWindow::on_pushButton_3_clicked()
{
    connect_flag =  !connect_flag;
    if(connect_flag)//can connect
    {
        QString connectIp = "127.0.0.1";
        int connectPort = 7002;
            socket->connectToHost(QHostAddress(connectIp),connectPort);//
            connect(socket,SIGNAL(readyRead()),this,SLOT(my_Receive()));//
            bool conn_status = socket->waitForConnected();
            if(conn_status)
            {
                qDebug()<<"Connect successful!";
                ui->label->setEnabled(true);
                ui->pushButton_2->setEnabled(true);
                ui->lineEdit->setEnabled(true);
                ui->label_4->setText(QString::fromLocal8Bit("已连接"));
                ui->pushButton_3->setText(QString::fromLocal8Bit("断开服务器"));
                 ui->pushButton->setEnabled(true);

            }
            else
            {
                qDebug()<<"Connect falied!";
                ui->label->setEnabled(false);
                ui->pushButton_2->setEnabled(false);
                ui->lineEdit->setEnabled(false);
                ui->label_4->setText(QString::fromLocal8Bit("未连接"));
                ui->pushButton_3->setText(QString::fromLocal8Bit("连接服务器"));

            }
    }
    else
    {
       socket->disconnectFromHost();
       ui->label->setEnabled(false);
       ui->pushButton_2->setEnabled(false);
       ui->lineEdit->setEnabled(false);

       ui->lineEdit->clear();

       ui->label_4->setText(QString::fromLocal8Bit("已断开连接"));
       ui->pushButton_3->setText(QString::fromLocal8Bit("连接服务器"));
        ui->pushButton->setEnabled(false);
        this->wav_data.clear();
        ui->textEdit->clear();
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName();
    qDebug()<<"File:"<<filename;
    ui->lineEdit->setText(filename);
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly ))
    {
        wav_data  = file.readAll();
        qDebug()<<"wav_data";
        qDebug()<<wav_data.toHex();

        qDebug()<<wav_data;

    }
    else
        qDebug()<<"file open error!";
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().length())
    {
        ui->textEdit->append(QString::fromLocal8Bit("正在开始评测 请稍后..."));
      //  socket->write("qwe");

        QByteArray array;
        array.push_back("0x01");
        array.push_back("0x02");
        array.push_back("0x03");
        array.push_back("0x04");
        array.push_back("0x05");
        array.push_back("0x06");
        array.push_back("0x07");
        array.push_back("0x00");
        array.push_back("0x08");

        qDebug()<<"size:"<<array.length();


        //socket->write(array);
        socket->write(wav_data);
       ui->textEdit->append(QString::fromLocal8Bit("文件信息"));
        ui->textEdit->append(QString::fromLocal8Bit("大小:") + wav_data.length());
        ui->textEdit->append(QString::fromLocal8Bit("内容") +  wav_data);

        ui->pushButton->setEnabled(false);
    }
    else
    {
        QMessageBox box;
        box.setText(QString::fromLocal8Bit("请先选择wav文件"));
        box.exec();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
}
