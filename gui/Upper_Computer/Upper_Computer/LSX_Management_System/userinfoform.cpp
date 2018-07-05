#include "userinfoform.h"
#include "ui_userinfoform.h"
#include <QPushButton>
#include <QGridLayout>
#include <QSqlQuery>
#include <qDebug>
#include "logindialog.h"

userInfoForm::userInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userInfoForm)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal );



    adminWidget = new QWidget();//admin


    publicWidget = new QWidget();//public


    adminLayout = new QGridLayout(adminWidget);//widget 添加布局管理

    publicLayout = new QGridLayout(publicWidget);//widget 添加布局管理

    addUser = new addUserForm();

    alterUser = new alterUserForm();
    connect(this,SIGNAL(toAlterUser(QString)),alterUser,SLOT(fromUserInfo(QString)));

    delUser = new delUserDialog();

//    //添加用户ui
//    addUser = new addUserForm();



//    //删除用户ui
//    delUser = new delUserDialog();

    //admin
    {
        //控制用户权限显示内容  管理员以及root用户有增删查改权限 可现实空间  普通用户不可见
            button1 = new QPushButton(adminWidget);
            button1->setText(QString::fromLocal8Bit("添加用户"));
            button2 = new QPushButton(adminWidget);
            button2 ->setText(QString::fromLocal8Bit("修改用户信息"));

            button3 = new QPushButton(adminWidget);
            button3 ->setText(QString::fromLocal8Bit("删除用户"));

            connect(button1,SIGNAL(clicked()),this,SLOT(addUserInfo()));
            connect(button2,SIGNAL(clicked()),this,SLOT(alterUserInfo()));
            connect(button3,SIGNAL(clicked()),this,SLOT(delUserInfo()));

            button1->setMinimumHeight(25);
            button2->setMinimumHeight(25);
            button3->setMinimumHeight(25);

    }
        //public
    {
       button4 = new QPushButton(publicWidget);
       button4->setMinimumHeight(25);
       button4 ->setText(QString::fromLocal8Bit("修改用户信息"));
       connect(button4,SIGNAL(clicked()),this,SLOT(alterUserInfo()));
    }

    ui->pushButton->setVisible(false);
//************************此消息不能在 userinfo构造函数中********************

}


void userInfoForm::fromMainWindow(QString string)
{
    bool admin = true;//用户权限控制 sql备用
    QString userName;
    QString userTel;
    ui->label_4->setText(string);//userinfo 中显示用户名
    QSqlQuery query;
    QString sql = QObject::tr("select * from `user` where userid ='%1'").arg(ui->label_4->text());
    query.prepare(sql);
    query.exec();
    while(query.next())
    {
        qDebug()<<"valuse====="<<query.value(6).toString();
        qDebug()<<"valuse====="<<query.value(6).toBool();
        admin = query.value(6).toBool();
        userName  = query.value(2).toString();
        userTel = query.value(7).toString();
    }
    if(admin)//根据当前用户的权限选择显示空间
    {
       // admin->show();
        ui->label_5->setText(QString::fromLocal8Bit("管理员"));
        adminLayout->addWidget(button1);
        adminLayout->addWidget(button2);
        adminLayout->addWidget(button3);
        ui->gridLayout->addWidget(adminWidget);// 管理员 添加到ui widget中
    }else
    {
        //public->show();
        ui->label_5->setText(QString::fromLocal8Bit("普通用户"));
        publicLayout->addWidget(button4);
        ui->gridLayout->addWidget(publicWidget);// 普通用户 添加到ui widget中
    }

    ui->label_6->setText(userName);
    ui->label_8->setText(userTel);




}



userInfoForm::~userInfoForm()
{
    delete ui;
}

void userInfoForm::alterUserInfo()//点击修改用户
{
        //修改用户ui
    alterUser->show();

        emit toAlterUser(ui->label_4->text());
        //alterUser->show();
}

void userInfoForm::addUserInfo()//点击添加用户
{
    addUser->show();

    //connect(this,SIGNAL(toAddUser()),addUser,SLOT(fromAddUserInfo()));
   // emit toAddUser();
}
void userInfoForm::delUserInfo()
{
   delUser->exec();
   // connect(this,SIGNAL(toAddUser()),addUser,SLOT(fromAddUserInfo()));
   // emit toAddUser();
}





void userInfoForm::on_pushButton_clicked()//退出当前用户 重新登录
{

    emit toLoginDialogForReLogin();//跳转到验证//toMainWindow
    qDebug()<<QString::fromLocal8Bit("信号触发");
//    qApp->closeAllWindows();
    //qApp->deleteLater();
//    qApp->exec();
//    qApp->exit(773);
}




