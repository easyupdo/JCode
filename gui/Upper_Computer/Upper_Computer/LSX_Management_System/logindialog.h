#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <app/mysqlsupport.h>
#include <QDateTime>

#include <QDialog>
#include <QMouseEvent>
#include "app/imessagebox.h"
#define LOGIN true
#define LOGOUT false
//#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    void reBootControl();

signals:
    void toMainWindow(QString,bool);
    void toMySqlSupport();
    void toDevicePollingForStartPolling();
    void toMainWindowForLoginState(bool);

public slots:
        void destoryMainWindow();
        void fromMainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_loginClosePushButton_clicked();


protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::LoginDialog *ui;
    bool bootType;

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下

//    MainWindow * w;

};

#endif // LOGINDIALOG_H
