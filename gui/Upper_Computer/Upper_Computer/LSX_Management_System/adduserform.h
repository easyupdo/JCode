#ifndef ADDUSERFORM_H
#define ADDUSERFORM_H

#include <QWidget>
#include "app/imessagebox.h"
#include <QSqlError>

namespace Ui {
class addUserForm;
}

class addUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit addUserForm(QWidget *parent = 0);
    ~addUserForm();
    void selectFormDb();//添加前先判断一下数据库中有没有
    int addToSql();

public slots:
    void fromAddUserInfo();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();


    void on_addDuan_CloseButton_clicked();


protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::addUserForm *ui;

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
};

#endif // ADDUSERFORM_H
