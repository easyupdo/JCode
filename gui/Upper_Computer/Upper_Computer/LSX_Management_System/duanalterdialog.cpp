#include "duanalterdialog.h"
#include "ui_duanalterdialog.h"

DuanAlterDialog::DuanAlterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuanAlterDialog)
{
    ui->setupUi(this);
}

DuanAlterDialog::~DuanAlterDialog()
{
    delete ui;
}
