#include "troublelogform.h"
#include "ui_troublelogform.h"

troubleLogForm::troubleLogForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::troubleLogForm)
{
    ui->setupUi(this);
}

troubleLogForm::~troubleLogForm()
{
    delete ui;
}
