#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QDebug>


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    bootType = false;
    this->setWindowTitle(QString::fromLocal8Bit("用户登录"));
    this->mousePressed = false;
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体关闭时自动释放内存
//    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    //global



}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_pushButton_clicked()
{
//    if(ui->lineEdit->text() == "admin" && ui->lineEdit_2->text()=="123456")//认证
//    {
        QSqlQuery query;
        QString sql  = QObject::tr("select * from `user` where userid = '%1'and password = '%2'").arg(ui->lineEdit->text(),ui->lineEdit_2->text());
        query.prepare(sql);
        query.exec();
        qDebug()<<sql;
        if(query.next())
        {
            QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd");
            QString operationString = QString::fromLocal8Bit("用户")+ui->lineEdit->text()+QString::fromLocal8Bit("登录");

            QSqlQuery iQuery;//用户登录log
            QString sql = QObject::tr("insert into log(userid,recorddate,operation) values('%1','%2','%3')").arg(ui->lineEdit->text(),time,operationString);
            qDebug()<<"currentTime:"<<time;
            qDebug()<<"sql"<<sql;
            iQuery.prepare(sql);
            iQuery.exec();

            iMessageBox box;
            box.setMessageType("prompt");//提示
            box.setMessageText(QString::fromLocal8Bit("欢迎使用!"));
            int ret = box.exec();
            qDebug()<<ret;
            if(ret == 1)
            {
                this->close();
                emit toMainWindow(ui->lineEdit->text(),query.value(6).toInt());//第二个参数用户权限控制代码;
                emit toMainWindowForLoginState(LOGIN);
            }else
            {
//                if(bootType)//1:重新登录  0:第一次登录
//                {
//                     this->close();
//                }
            } //闪烁窗口
        }else
        {
            emit toMainWindowForLoginState(LOGOUT);
            ui->lineEdit_2->clear();
            QMessageBox *box = new QMessageBox;
            box->setText(QString::fromLocal8Bit("用户名或密码错误 请重新输入"));
            box->exec();
        }
         emit toDevicePollingForStartPolling();
}

void LoginDialog::on_pushButton_2_clicked()
{
//    qDebug()<<QString::fromLocal8Bit("bootType")<<bootType;
//    if(!bootType)//1:重新登录  0:第一次登录
//    {
//        qApp->closeAllWindows();
//    }
    close();
}

void LoginDialog::destoryMainWindow()
{
//    delete w;
}


void LoginDialog::fromMainWindow()
{
    qDebug()<<QString::fromLocal8Bit("信号来自DeviceControl->FromMainWindwos!");
    emit toMySqlSupport();
}

void LoginDialog::reBootControl()
{
    qDebug()<<QString::fromLocal8Bit("接收到重登信息号");
    bootType = true;//bootType =   1:重登录  0:第一次登录
}

void LoginDialog::on_loginClosePushButton_clicked()
{
    on_pushButton_2_clicked();
}


void LoginDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void LoginDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
