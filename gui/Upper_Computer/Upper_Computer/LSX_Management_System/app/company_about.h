#ifndef COMPANY_ABOUT_H
#define COMPANY_ABOUT_H

#include <QDialog>

namespace Ui {
class company_About;
}

class company_About : public QDialog
{
    Q_OBJECT

public:
    explicit company_About(QWidget *parent = 0);
    ~company_About();

private:
    Ui::company_About *ui;
};

#endif // COMPANY_ABOUT_H
