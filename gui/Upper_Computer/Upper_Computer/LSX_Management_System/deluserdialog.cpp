#include "deluserdialog.h"
#include "ui_deluserdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>

delUserDialog::delUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delUserDialog)
{
    ui->setupUi(this);
    this->mousePressed = false;
    this->setWindowFlags(Qt::FramelessWindowHint);
    setSelectUser();
}

delUserDialog::~delUserDialog()
{
    delete ui;
}

void delUserDialog::on_pushButton_clicked()
{
    QSqlQuery query;
    iMessageBox box;
    box.setUserMessage(QString::fromLocal8Bit("确认要删除吗?"),"ask");
    if(box.exec())
    {
        QString sql = QObject::tr("DELETE FROM USER WHERE userid = '%1'").arg(ui->comboBox->currentText());
        query.prepare(sql);
        if(query.exec())
        {
            box.setUserMessage(QString::fromLocal8Bit("已经删除!"),"prompt");
            box.exec();
        }else
        {
            box.setUserMessage(QString::fromLocal8Bit("删除出错!  错误代码:")+query.lastError().nativeErrorCode(),"error");
            box.exec();
        }
        this->close();
    }



}


void delUserDialog::setSelectUser()
{
    ui->comboBox->clear();
    QSqlQuery query;
    QString sql = QObject::tr("select userid,status from `user`");
    query.prepare(sql);
    query.exec();
    while(query.next())
    {
        if(query.value(1).toBool() == true)//剥离管理员
            continue;
        ui->comboBox->addItem(query.value(0).toString());
    }

//    if(query.exec())
//    {
//        QMessageBox box;
//        box.setText(QString::fromLocal8Bit(""));
//    }
}

void delUserDialog::on_addDuan_CloseButton_clicked()
{
    this->close();
}


void delUserDialog::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void delUserDialog::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void delUserDialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void delUserDialog::on_pushButton_2_clicked()
{
    this->close();
}
