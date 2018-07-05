#ifndef ADDDEVICEDIALOG_H
#define ADDDEVICEDIALOG_H

#include <QDialog>
#include "deviceinfodialog.h"
#include <app/global.h>
#include <QComboBox>
#include <QLineEdit>
#include "app/imessagebox.h"
#include <QSqlError>

namespace Ui {
class AddDeviceDialog;
}

class AddDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDeviceDialog(QWidget *parent = 0);
    ~AddDeviceDialog();
public:
    void setCombobox();
    void addTocombobox(QString sql,QComboBox *box);
//    void addToLineEdit(QString sql,QLineEdit *lineEdit);

    void messageWarring(QString);
    void setOther();

signals:
    void toDeviceManagementFormForSentAddInfo(QString []);





private slots:


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_comboBox_3_currentTextChanged(const QString &arg1);

//    void on_comboBox_4_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

//    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_addDuan_CloseButton_clicked();

private:
    Ui::AddDeviceDialog *ui;
    DeviceInfoDialog * deviceInfo;
    global * sqlGlobal;

    QSqlQuery * query;
    QString sqlText[4];

    bool deviceidAllocControl;
};

#endif // ADDDEVICEDIALOG_H
