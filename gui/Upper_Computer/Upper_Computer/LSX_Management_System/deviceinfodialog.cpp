#include "deviceinfodialog.h"
#include "ui_deviceinfodialog.h"

DeviceInfoDialog::DeviceInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceInfoDialog)
{
    ui->setupUi(this);
}

DeviceInfoDialog::~DeviceInfoDialog()
{
    delete ui;
}

void DeviceInfoDialog::on_tabWidget_destroyed()
{
   // if()

    ui->pushButton_3->setText("添加电段");
}

void DeviceInfoDialog::on_pushButton_3_clicked()
{
    duanAdd = new DuanDialog();
    duanAdd->exec();
}

void DeviceInfoDialog::on_pushButton_4_clicked()
{
    duanAlter = new DuanAlterDialog();
    duanAlter->exec();
}
