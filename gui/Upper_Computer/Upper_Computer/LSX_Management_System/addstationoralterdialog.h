#ifndef ADDSTATIONORALTERDIALOG_H
#define ADDSTATIONORALTERDIALOG_H

#include <QDialog>
#include "app/imessagebox.h"
#include <QSqlQuery>

namespace Ui {
class addStationOrAlterDialog;
}

class addStationOrAlterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addStationOrAlterDialog(QWidget *parent = 0);
    ~addStationOrAlterDialog();
    void fromDeviceManagementFormForAlterStation(bool status, QString  stringMsg[]);
    void Station();

    void setComboBox_duan();
    void setComboBox_jian(QString duan);
    void setComboBox_qu(QString jian);
signals:
    void toDeviceManagementForUpdateTableview_2_Show(QString);


private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_addDuan_CloseButton_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::addStationOrAlterDialog *ui;
    bool alterNoSelectFlag;

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
};

#endif // ADDSTATIONORALTERDIALOG_H
