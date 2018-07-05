#ifndef ALTERDEVICEDIALOG_H
#define ALTERDEVICEDIALOG_H

#include <QDialog>
#include "deviceinfodialog.h"
#include <QComboBox>
#include "app/global.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "app/imessagebox.h"
namespace Ui {
class AlterDeviceDialog;
}

class AlterDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlterDeviceDialog(QWidget *parent = 0);
    ~AlterDeviceDialog();

public:
    void setCombobox();
    void addTocombobox(QString sql,QComboBox *box);
    void setCombobox(QString * comboboxString);
    void messageWarring(QString message);

private slots:
  //  void on_pushButton_7_clicked();





    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AlterDeviceDialog *ui;
    DeviceInfoDialog * deviceInfo;

    global * sqlGlobal;

    QSqlQuery * query;

};

#endif // ALTERDEVICEDIALOG_H
