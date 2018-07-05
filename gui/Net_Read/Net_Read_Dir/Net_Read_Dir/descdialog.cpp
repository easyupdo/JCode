#include "descdialog.h"
#include "ui_descdialog.h"

DescDialog::DescDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DescDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("说明"));
}

DescDialog::~DescDialog()
{
    delete ui;
}
