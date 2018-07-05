#include "adduserform.h"
#include "ui_adduserform.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

addUserForm::addUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addUserForm)
{
    ui->setupUi(this);
    this->mousePressed = false;
    this->setWindowTitle(QString::fromLocal8Bit("添加用户"));
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password );
//    ui->lineEdit->setMaxLength(8);
    ui->lineEdit_2->setMaxLength(8);
//    QRegExp regx("^[\u4e00-\u9fa5]*$");//正则表达式
//     QValidator *validator = new QRegExpValidator(regx, this );
//     ui->lineEdit->setValidator(validator);
}

addUserForm::~addUserForm()
{
    delete ui;
}


void addUserForm::on_pushButton_clicked()//添加
{

    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "" )
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("用户名或者密码为空!"),"error");
        box.exec();
    }else
    {
        if(ui->lineEdit_2->text() != ui->lineEdit_7->text())
        {
            iMessageBox box ;
            box.setUserMessage(QString::fromLocal8Bit("两次用户密码不同!"),"error");
            box.exec();
        }else
        {
            selectFormDb();//添加前先判断一下 库里有没有改用户
            int errorCode = addToSql();
            if(errorCode)
            {
                iMessageBox box;
                box.setUserMessage(QString::fromLocal8Bit("用户名已经存在!"),"error");
                box.exec();
            }
        }
    }
 }

void addUserForm::selectFormDb()
{
    QSqlQuery query;
    if(query.exec("select userid from `user`wehre userid = ui->lineEdit->text()"))//用户名
    {
        while(query.next())
        {
            qDebug()<<QString::fromLocal8Bit("用户名应景存在:")<<query.value(0);
            if(query.value(0) == ui->lineEdit->text())
            {
                iMessageBox box;
                box.setUserMessage(QString::fromLocal8Bit("用户名已经存在!"),"prompt");
                box.exec();
            }
        }
    }
}

int addUserForm::addToSql()
{
    QString insert_user = QObject::tr("INSERT INTO `user`(userid,`Password`,`name`,age,sex,Telephone)value('%1','%2','%3','%4','%5','%6')").arg(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text(),ui->lineEdit_5->text(),ui->lineEdit_6->text());
    qDebug()<<"Insert:"<<insert_user;
    QSqlQuery query;
    query.prepare(insert_user);
    query.exec();
    qDebug()<<QString::fromLocal8Bit("错误:")<<query.lastError().text()<<query.lastError().nativeErrorCode();
    if(query.lastError().nativeErrorCode().toInt())
    return query.lastError().nativeErrorCode().toInt() ;
    ui->lineEdit->text();
    QString userid = QObject::tr("select userid from `user` where userid =%1").arg(ui->lineEdit->text());//查询数据库是否存在  安全方式
    query.prepare(userid);
    query.exec();
    QMessageBox box;
    if(query.next())
    {
        qDebug()<<"lineEdit:"<<ui->lineEdit->text();
        qDebug()<<"query"<<query.value(0).toString();
        if(query.value(0).toString() == ui->lineEdit->text())
        {
            box.setText(QString::fromLocal8Bit("已添加"));
        }
    }else
    box.setText(QString::fromLocal8Bit("添加错误"));

    if(box.exec() == QMessageBox::Ok)
    {
         this->close();
    }

    qDebug()<<ui->lineEdit->text();
    return 0;

}








//没有用
void addUserForm::fromAddUserInfo()
{

}

void addUserForm::on_pushButton_2_clicked()
{
    this->close();
}


void addUserForm::on_addDuan_CloseButton_clicked()
{
    this->close();
}




void addUserForm::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void addUserForm::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void addUserForm::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
