#ifndef DELUSERDIALOG_H
#define DELUSERDIALOG_H

#include <QDialog>
#include <app/imessagebox.h>
#include <QMouseEvent>
#include <QSqlError>

namespace Ui {
class delUserDialog;
}

class delUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit delUserDialog(QWidget *parent = 0);
    ~delUserDialog();

    void setSelectUser();

private slots:
    void on_pushButton_clicked();

    void on_addDuan_CloseButton_clicked();

    void on_pushButton_2_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::delUserDialog *ui;

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下
};

#endif // DELUSERDIALOG_H
