#include "alteruserform.h"
#include "ui_alteruserform.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

alterUserForm::alterUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alterUserForm)
{
    ui->setupUi(this);
    mousePressed = false;
    ui->lineEdit_14->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

alterUserForm::~alterUserForm()
{
    delete ui;
}


void alterUserForm::fromUserInfo(QString string)//参数:当前用户名
{
    ui->comboBox->clear();

    QSqlQuery query;
    QString sqlAdmin = QObject::tr("select * from `user` where userid = '%1'").arg(string);
    QString sqlPublic = QObject::tr("select userid  from `user`");
    query.prepare(sqlAdmin);
    query.exec();
    qDebug()<<"sql:"<<sqlAdmin;
    while(query.next())
    {
        qDebug()<<"string:"<<query.value(6).toBool();
        if(query.value(6).toBool() == true)//admin 有权限管理其他用户
        {
            QSqlQuery allQuery;
            allQuery.prepare(sqlPublic);
            allQuery.exec();
            qDebug()<<"sqlPublic"<<sqlPublic;
            while(allQuery.next())
            {
                ui->comboBox->addItem(allQuery.value(0).toString());
            }
            ui->label_9->setText(string);//当前用户名
            ui->label_10->setText(QString::fromLocal8Bit("管理员"));
            ui->label_11->setText(QString::fromLocal8Bit("(您可修改所有用户信息!)"));
            on_comboBox_activated(ui->comboBox->currentText());//管理员选择用户
        }else//public 普通用户 只能修改自己
        {
            ui->label_9->setText(string);//当前用户名
            ui->label_10->setText(QString::fromLocal8Bit("普通用户"));
            ui->label_11->setText(QString::fromLocal8Bit("(您仅可修改当前用户信息!)"));
            ui->comboBox->addItem(string);
            ui->lineEdit_2->setText(query.value(1).toString());
            ui->lineEdit_3->setText(query.value(2).toString());//联系人
            ui->lineEdit_4->setText(query.value(3).toString());//年龄
            ui->lineEdit_5->setText(query.value(4).toString());//性别
            ui->lineEdit_6->setText(query.value(7).toString());//电话

            ui->lineEdit_13->setText(string);//修改的用户名空间  用户名一次性 用户不允许修改

            ui->lineEdit_14->setText(query.value(1).toString());
            ui->lineEdit_15->setText(query.value(2).toString());//联系人
            ui->lineEdit_16->setText(query.value(3).toString());//年龄
            ui->lineEdit_17->setText(query.value(4).toString());//性别
            ui->lineEdit_18->setText(query.value(7).toString());//电话
        }
    }

}



void alterUserForm::on_pushButton_clicked()//修改到数据库
{
    iMessageBox box;
    box.setUserMessage(QString::fromLocal8Bit("您确定要修改吗?"),"ask");
    if(box.exec())
    {
        QSqlQuery query;
        QString userId = ui->lineEdit_13->text();
        QString passWord = ui->lineEdit_14->text();
        QString userName = ui->lineEdit_15->text();
        QString userAge = ui->lineEdit_16->text();
        QString userSex = ui->lineEdit_17->text();
        QString userTel = ui->lineEdit_18->text();

        //插入sql//QString sql = QObject::tr("insert into `user` (userid,password,name,age,sex,,telephone) values('%1','%2','%3','%4','%5','%6')").arg(userId,passWord,userName,userAge,userSex,userTel);
        QString sql = QObject::tr("update user set password = '%1',name = '%2',age = '%3',sex='%4',telephone='%5' where userid = '%6'").arg(passWord,userName,userAge,userSex,userTel,userId);
        query.prepare(sql);

        if(query.exec())
        {
            box.setUserMessage(QString::fromLocal8Bit("已修改"),"prompt");
        }else
        {
            box.setUserMessage(QString::fromLocal8Bit("修改失败!  错误代码:")+query.lastError().nativeErrorCode() ,"error");
        }
        box.exec();
        this->close();
    }

}

void alterUserForm::on_pushButton_2_clicked()
{
    this->close();
}

void alterUserForm::on_comboBox_activated(const QString &arg1)//管理员选择用户
{
    QSqlQuery query;
    QString sql = QObject::tr("select `password`,`name`,age,sex,telephone from `user` where userid = '%1'").arg(ui->comboBox->currentText());
    query.prepare(sql);
    query.exec();
    while(query.next())
    {
        ui->lineEdit_2->setText(query.value(0).toString());
        ui->lineEdit_3->setText(query.value(1).toString());//联系人
        ui->lineEdit_4->setText(query.value(2).toString());//年龄
        ui->lineEdit_5->setText(query.value(3).toString());//性别
        ui->lineEdit_6->setText(query.value(4).toString());//电话

        ui->lineEdit_13->setText(ui->comboBox->currentText());//修改的用户名空间  用户名一次性 用户不允许修改

        ui->lineEdit_14->setText(query.value(0).toString());
        ui->lineEdit_15->setText(query.value(1).toString());//联系人
        ui->lineEdit_16->setText(query.value(2).toString());//年龄
        ui->lineEdit_17->setText(query.value(3).toString());//性别
        ui->lineEdit_18->setText(query.value(4).toString());//电话
    }
}



void alterUserForm::on_addDuan_CloseButton_clicked()
{
    this->close();
}


void alterUserForm::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void alterUserForm::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void alterUserForm::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
