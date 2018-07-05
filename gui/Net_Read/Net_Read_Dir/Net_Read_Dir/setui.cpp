#include "setui.h"
#include "ui_setui.h"

SetUi::SetUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetUi)
{
    ui->setupUi(this);
    codeEditStatus = LOCK;
    setAllLineEdit(LOCK);//init


    this->setWindowTitle(QString::fromLocal8Bit("设置"));
}

SetUi::~SetUi()
{
    delete ui;
}


QSettings* SetUi::getSettings()
{
    QString appPath = QApplication::applicationDirPath();
    qDebug()<<"App Path:"<<appPath;
    QString ecodeINIFile = appPath + "/conf/ecode.ini";
    QSettings *setting = new QSettings(ecodeINIFile,QSettings::IniFormat);

    return setting;
}


void SetUi::showCode()
{
    QSettings *setting = getSettings();
    QString codeString = setting->value("/code/code").toString();
    qDebug()<<"code:"<<codeString.toLatin1();
    char *c;
    char* one;
    QString lineEdit_Ptr;

    for(int i = 0;i<8;i++)
    {
        QString sb = codeString.mid(i*3,2);

        switch(i)
        {
        case 0:
            ui->lineEdit->setText(sb);
        case 1:
            ui->lineEdit_2->setText(sb);
        case 2:
            ui->lineEdit_3->setText(sb);
        case 3:
            ui->lineEdit_4->setText(sb);
        case 4:
            ui->lineEdit_5->setText(sb);
        case 5:
            ui->lineEdit_6->setText(sb);
        case 6:
            ui->lineEdit_7->setText(sb);
        case 7:
            ui->lineEdit_8->setText(sb);

        }
        QByteArray ab = sb.toLatin1();
        long tc =strtol(ab,&c,16);
        qDebug()<<"INT:"<<tc;
        btcode.tblCode[i] = tc;

        qDebug()<<"16:"<<QString::number(i,16);
    }

    delete (setting);

}

MN_ECODE SetUi::getCode()
{
    return btcode;
}

void SetUi::on_pushButton_clicked()
{
    codeEditStatus = !codeEditStatus;
    if(codeEditStatus)
        setAllLineEdit(codeEditStatus);
    else
         setAllLineEdit(codeEditStatus);


}

void SetUi::setAllLineEdit(bool status)
{
    ui->lineEdit->setEnabled(status);
    ui->lineEdit_2->setEnabled(status);
    ui->lineEdit_3->setEnabled(status);
    ui->lineEdit_4->setEnabled(status);
    ui->lineEdit_5->setEnabled(status);
    ui->lineEdit_6->setEnabled(status);
    ui->lineEdit_7->setEnabled(status);
    ui->lineEdit_8->setEnabled(status);
}


//修改密码保存
void SetUi::on_pushButton_2_clicked()
{
    QSettings *setting = getSettings();

    QString code = ui->lineEdit->text()+"-"+ui->lineEdit_2->text()+"-"+ui->lineEdit_3->text()+"-"+ui->lineEdit_4->text()+"-"+ui->lineEdit_5->text()+"-"+ui->lineEdit_6->text()+"-"+ui->lineEdit_7->text()+"-"+ui->lineEdit_8->text();
    setting->setValue("/code/code",code);
    this->close();

    setAllLineEdit(LOCK);

    delete setting;



}

void SetUi::on_pushButton_3_clicked()
{
    this->close();
}
