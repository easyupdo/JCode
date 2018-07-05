#ifndef ADDORALTERJIANDIALOG_H
#define ADDORALTERJIANDIALOG_H

#include <QDialog>
#include <app/imessagebox.h>
#include <QSqlQuery>

namespace Ui {
class addOrAlterJianDialog;
}

class addOrAlterJianDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addOrAlterJianDialog(QWidget *parent = 0);
    ~addOrAlterJianDialog();
    void Jian();
    void setComboBox();
public slots:
    void fromDeviceManagementFormForAlterJian(bool status, QString  stringMsg[]);

signals:
    void toDeviceManagementForUpdateTableview_2_Show(QString);

private slots:
    void on_addDuan_CloseButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addOrAlterJianDialog *ui;
    bool alterNoSelectFlag;
};

#endif // ADDORALTERJIANDIALOG_H
