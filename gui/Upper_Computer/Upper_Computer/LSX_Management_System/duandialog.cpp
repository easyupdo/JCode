#include "duandialog.h"
#include "ui_duandialog.h"

DuanDialog::DuanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuanDialog)
{
    ui->setupUi(this);
}

DuanDialog::~DuanDialog()
{
    delete ui;
}
