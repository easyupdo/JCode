#include "sysmanagementform.h"
#include "ui_sysmanagementform.h"
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>

userManagementForm::userManagementForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userManagementForm)
{
    ui->setupUi(this);
    fileDialog = new QFileDialog(this);
    this->readINI();

}

userManagementForm::~userManagementForm()
{
    delete ui;
}

void userManagementForm::on_pushButton_clicked()
{
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择目录"), QDir::currentPath()));
    qDebug()<<QString::fromLocal8Bit("用户选择目录")<<directory;
    if(directory != "")
    {
        ui->lineEdit->setText(directory);
        emit this->changeVoiceDownRootDir(directory);
        this->writeINI(directory,"tmp");
    }


}

void userManagementForm::on_pushButton_2_clicked()
{
     QString directory = QDir::toNativeSeparators(fileDialog->getExistingDirectory(this, QString::fromLocal8Bit("选择目录"), QDir::currentPath()));
     if(directory != "")
     {
         qDebug()<<"hahahah";
         this->writeINI(directory,"download");
     }
}

void userManagementForm::readINI()
{
    QString AppPath = QCoreApplication::applicationDirPath();
    QString configIniFile = AppPath + "/config" + "/config.ini";
    QSettings settings(configIniFile,QSettings::IniFormat);

    settings.beginGroup("Path");
    QString nPath = settings.value("voiceDownloadPath").toString();
    QString tmpPath = settings.value("voiceTmpPath").toString();
    settings.endGroup();
    qDebug()<<"nPath"<<nPath;
    ui->lineEdit_2->setText(nPath);
    ui->lineEdit->setText(tmpPath);
}


void userManagementForm::writeINI(QString savePath,QString what)
{
    QString AppPath = QCoreApplication::applicationDirPath();
    QString configIniFile = AppPath + "/config" + "/config.ini";
    qDebug()<<"configIniFile:"<<configIniFile;
    QSettings settings(configIniFile, QSettings::IniFormat);

        if(settings.isWritable())
        {
            settings.beginGroup("Path");
            if(what == "download")
            {
                settings.setValue("voiceDownloadPath",savePath);
                ui->lineEdit_2->setText(savePath);
            }
            else if(what == "tmp")
            {
                settings.setValue("voiceTmpPath",savePath);
                ui->lineEdit->setText(savePath);
            }
            settings.sync();
            settings.endGroup();
            qDebug()<<"ini_Write status:"<<settings.status();
        }else
        {
            QMessageBox box;
            box.setText(QString::fromLocal8Bit("修改失败"));
            box.exec();
        }




}
