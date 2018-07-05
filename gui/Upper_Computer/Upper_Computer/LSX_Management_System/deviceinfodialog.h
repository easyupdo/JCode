#ifndef DEVICEINFODIALOG_H
#define DEVICEINFODIALOG_H

#include <QDialog>
#include "duanalterdialog.h"
#include "duandialog.h"

namespace Ui {
class DeviceInfoDialog;
}

class DeviceInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceInfoDialog(QWidget *parent = 0);
    ~DeviceInfoDialog();

private slots:
    void on_tabWidget_destroyed();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DeviceInfoDialog *ui;
    DuanAlterDialog * duanAlter;
    DuanDialog * duanAdd;
};

#endif // DEVICEINFODIALOG_H
