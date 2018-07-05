#ifndef FAULTSEARCHDIALOG_H
#define FAULTSEARCHDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include  "app/imessagebox.h"
#include <QSqlError>
#include <QHeaderView>
#include <QScrollBar>

//#define

namespace Ui {
class faultSearchDialog;
}

class faultSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit faultSearchDialog(QWidget *parent = 0);
    ~faultSearchDialog();
    void setComboBox();
    void setFaultType();
    void setDevice_Duan_Jian_Qu_Station(QString what);
    void setComboBoxAllInit();
    void setDevice_Talveview();//按照设备方式查询显示到tableview中
    void setTableviewHeadview();

public slots:
    void fromMainWindowForDeviceInfo(QString *deviceInfo);


private slots:
    void on_comboBox_6_activated(const QString &arg1);

    void on_comboBox_7_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_comboBox_3_activated(const QString &arg1);

    void on_comboBox_4_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::faultSearchDialog *ui;
    QSqlQueryModel * queryModel;
};

#endif // FAULTSEARCHDIALOG_H
