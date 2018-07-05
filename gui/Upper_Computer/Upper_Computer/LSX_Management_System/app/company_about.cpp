#include "company_about.h"
#include "ui_company_about.h"

company_About::company_About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::company_About)
{
    ui->setupUi(this);
}

company_About::~company_About()
{
    delete ui;
}
