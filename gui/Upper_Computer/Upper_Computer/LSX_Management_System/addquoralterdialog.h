#ifndef ADDQUORALTERDIALOG_H
#define ADDQUORALTERDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include  "app/imessagebox.h"
#include  <QMouseEvent>

namespace Ui {
class addQuOrAlterDialog;
}

class addQuOrAlterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addQuOrAlterDialog(QWidget *parent = 0);
    ~addQuOrAlterDialog();

    void setComboBox_duan();
    void setComboBox_jian(QString duan);
    void Qu();
signals:
    void toDeviceManagementForUpdateTableview_2_Show(QString);

public slots:
    void fromDeviceManagementFormForAlterQu(bool status, QString stringMsg[]);

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_addDuan_CloseButton_clicked();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::addQuOrAlterDialog *ui;
    bool alterNoSelectFlag;

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
};

#endif // ADDQUORALTERDIALOG_H
