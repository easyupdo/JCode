#include "adddevicedialog.h"
#include "ui_adddevicedialog.h"
#include <QMessageBox>

AddDeviceDialog::AddDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDeviceDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setWindowTitle(QString::fromLocal8Bit("添加设备"));
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

//    setCombobox();//SET DUAN COMBOBOX

    ui->label_5->setEnabled(false);
//    ui->lineEdit_2->setEnabled(false);
    deviceidAllocControl = true;


}

AddDeviceDialog::~AddDeviceDialog()
{
    delete ui;
}


void AddDeviceDialog::setCombobox()
{
    QString sql =  this->sqlGlobal->addDevice_SQL_Select(sqlText,0);
    qDebug()<<"sql:"<<sql;
    this->query->prepare(sql);
    this->query->exec();
    while(this->query->next())
    {
        ui->comboBox->addItem(this->query->value(0).toString());
    }
    setOther();
}



//void AlterDeviceDialog::on_pushButton_7_clicked()
//{
//    deviceInfo = new DeviceInfoDialog();
//    deviceInfo->exec();
//}




//抽象出来 代码复用
void AddDeviceDialog::addTocombobox(QString sql,QComboBox *box)
{
    qDebug()<<"combobox_Sql；"<<sql;
    box->clear();
    QSqlQuery query;
    query.prepare(sql);
    query.exec();
    while(query.next())
    {
        box->addItem(query.value(0).toString());
    }

}

//void addToLineEdit(QString sql,QLineEdit *lineEdit)
//{
////    QSqlQuery query;
////    query.prepare(sql);
////    query.exec();
////    while(query.next())
////    {
////        lineEdit->setText();
////    }
//}


//duan
void AddDeviceDialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    sqlText[0]=ui->comboBox->currentText();//duan
      QString sql = this->sqlGlobal->addDevice_SQL_Select(sqlText,1);
      addTocombobox(sql,ui->comboBox_2);
      qDebug()<<"SSSSSSSSSSSSS";
}
//jian
void AddDeviceDialog::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    sqlText[1]=ui->comboBox_2->currentText();//jian
    QString sql = this->sqlGlobal->addDevice_SQL_Select(sqlText,2);
    addTocombobox(sql,ui->comboBox_3);
}
//qu
void AddDeviceDialog::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    sqlText[2]=ui->comboBox_3->currentText();//qu
    QString sql = this->sqlGlobal->addDevice_SQL_Select(sqlText,3);
    addTocombobox(sql,ui->comboBox_4);
}

//void AddDeviceDialog::on_comboBox_4_currentTextChanged(const QString &arg1)
//{
//    sqlText[3]=ui->comboBox_4->currentText();//station
//    QString sql = this->sqlGlobal->addDevice_SQL_Select(sqlText,4);
//    addToLineEdit(sql,ui->lineEdit_2);
//}


void AddDeviceDialog::on_pushButton_clicked()
{
    qDebug()<<"ip"<<ui->spinBox->text();
    QString whereText[7];
    whereText[0] = ui->comboBox->currentText();
    whereText[1] = ui->comboBox_2->currentText();
    whereText[2] = ui->comboBox_3->currentText();
    whereText[3] = ui->comboBox_4->currentText();
    whereText[4] = ui->lineEdit_2->text();
    whereText[5] = ui->spinBox->text()+"."+ui->spinBox_2->text()+"."+ui->spinBox_3->text()+"."+ui->spinBox_4->text();
    whereText[6] = ui->lineEdit->text();
    qDebug()<<"ip地址:"<<whereText[5];
    if(whereText[0] == "")
        //************************************************************** 添加警告信息
    {
        messageWarring(QString::fromLocal8Bit("没有可用电务段"));
       goto out;
    }
    else if(whereText[1] == "")
    {
        messageWarring(QString::fromLocal8Bit("请选择车间"));
        goto out;
    }
    else if(whereText[2] == "")
    {
        messageWarring(QString::fromLocal8Bit("请选择工区"));
       goto out;
    }
    else if(whereText[3] == "")
    {
        messageWarring(QString::fromLocal8Bit("请选择车站"));
        goto out;
    }
    else if(whereText[4] == "")
    {
        messageWarring(QString::fromLocal8Bit("请填写设备号码"));
        goto out;
    }
    {
        qDebug()<<"选择错误："<<whereText[0];
        qDebug()<<"选择错误："<<whereText[1];
        qDebug()<<"选择错误："<<whereText[2];
        qDebug()<<QString::fromLocal8Bit("车站：")<<whereText[3];
        QString sql = this->sqlGlobal->addDeviceToMysql(whereText);
        qDebug()<<"执行sql:"<<sql;

        QSqlQuery query;
        query.prepare(sql);
        int ret = query.exec();
        iMessageBox box;
        if(ret)
        {
            box.setUserMessage(QString::fromLocal8Bit("添加成功"),"prompt");
        }else
            box.setUserMessage(QString::fromLocal8Bit("错误! 错误代码:'%1'").arg(query.lastError().nativeErrorCode() + query.lastError().text()),"error");

        box.exec();
        this->close();
        emit toDeviceManagementFormForSentAddInfo(whereText);

    }

    out:
    ;
}

void AddDeviceDialog::messageWarring(QString message)
{
    QMessageBox *box = new QMessageBox;
    box->setText(message);
    box->exec();
}



//void AddDeviceDialog::on_pushButton_3_clicked()
//{
//    if(deviceidAllocControl)
//    {
//        ui->label_5->setEnabled(true);
//        ui->lineEdit_2->setEnabled(true);
////        ui->pushButton_3->setText(QString::fromLocal8Bit("系统分配"));
//    }else
//    {
//        ui->label_5->setEnabled(false);
//        ui->lineEdit_2->setEnabled(false);
////        ui->pushButton_3->setText(QString::fromLocal8Bit("手动分配"));
//    }
//    deviceidAllocControl =!deviceidAllocControl;
//    qDebug()<<"deviceidAllocControl"<<deviceidAllocControl;
//}

void AddDeviceDialog::on_pushButton_2_clicked()
{
    this->close();
}


void AddDeviceDialog::on_addDuan_CloseButton_clicked()
{
    this->close();
}

void AddDeviceDialog::setOther()
{
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);
    ui->spinBox_4->setValue(0);
    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("0");
}
