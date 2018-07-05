#ifndef ALTERUSERFORM_H
#define ALTERUSERFORM_H

#include <QWidget>
#include <QMouseEvent>
#include "app/imessagebox.h"
#include <QSqlError>

namespace Ui {
class alterUserForm;
}

class alterUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit alterUserForm(QWidget *parent = 0);
    ~alterUserForm();

public slots:
    void fromUserInfo(QString string);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_activated(const QString &arg1);


    void on_addDuan_CloseButton_clicked();


protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::alterUserForm *ui;
    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
};

#endif // ALTERUSERFORM_H
