#ifndef ADDDUAN_DIALOG_H
#define ADDDUAN_DIALOG_H

#include <QDialog>
#include  "app/imessagebox.h"
#include <QMouseEvent>

namespace Ui {
class addDuan_Dialog;
}

class addDuan_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDuan_Dialog(QWidget *parent = 0);
    ~addDuan_Dialog();
    void addDuan();
//    void setDuanComboBox();
signals:
    void toDeviceManagementForUpdateTableview_2_Show(QString);
public slots:
    void fromDeviceManagementFormForJudgeAddOrAlter(bool status, QString stringMsg[]);

private slots:
    void on_pushButton_clicked();

    void on_addDuan_CloseButton_clicked();

    void on_pushButton_2_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::addDuan_Dialog *ui;
    bool alterNoSelectFlag;
    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
};

#endif // ADDDUAN_DIALOG_H
