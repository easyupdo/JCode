#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include"devicecontrolform.h"
#include"devicepollingform.h"
#include "adddevicedialog.h"
#include "devicemanagementform.h"
#include "app/mysqlsupport.h"
#include "app/global.h"
#include "addUserForm.h"
#include "alteruserform.h"
#include "deluserdialog.h"
#include "userlogform.h"
#include "userinfoform.h"
#include "troublelogform.h"
#include "sysmanagementform.h"
#include "app/company_about.h"
#include "logindialog.h"
#include "app/imessagebox.h"
#include "faultsearchdialog.h"
#include <QMouseEvent>
#include "qntp/NtpClient.h"
#include "qntp/NtpReply.h"
#include "qntp/QNtp.h"
#include <QHostAddress>

#define PADDING 2
namespace Ui {
class MainWindow;
}

enum Direction{
    UP = 0,
    DOWN=1,
    LEFT,
    RIGHT,
    LEFTTOP,
    LEFTBOTTOM,
    RIGHTBOTTOM,
    RIGHTTOP,
    NONE
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void btn_place();
    void reBootLoginDialog();


signals:
    void toUserInfo(QString);//第二个参数 1：重新登陆操作 0：第一次登录
    void toDeviceControl(QString);
    void toLoginDialog();
    void toDeviceControlForSaveInfo();
    void toDevicePollingForAccessControl(bool);
    void toDeviceManagementForAccessControl(bool);
    void toDeviceControlForDeviceInfo(QString *);
    void toDeviceFaultSearchForDeviceInfo(QString *);


public slots:
    void fromLoginDialog(QString, bool userType);
    void fromSysAdmin(QString);
    void fromDeviceControl();
    void fromUserInfoForReLogin();
    void fromLoginDialogForLoginState(bool loginState);

     void fromPollingForDeviceInfo(QString *string, bool pageType);
private slots:
    void onReplyReceived(QHostAddress host, quint16 port, NtpReply reply);

public:
    //窗口坐标
    bool maxOrNormal;//初始化状态
    int wid;//设置显示位置【横坐标】
    int ui_width;//界面宽度
    int desk_width;//屏幕宽度

    //窗口移动控制标志
    bool mousePressed; //鼠标按压标志
    QPoint mousePoint;
    bool windowsMove;
     QString userid;


protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void region(const QPoint &cursorGlobalPoint);


private slots:

    void on_minButton_clicked();

    void on_maxButton_clicked();

    void on_closeButton_clicked();

    void showCurrentTime();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();


    void on_loginButton_clicked();

    void on_logoutButton_clicked();

private:
    Ui::MainWindow *ui;



    MysqlSupport *mysql;
    DeviceControlForm * deviceControl;

    DevicePollingForm * devicePolling;

    DeviceManagementForm * deviceManagement;

    global * globalF;


    userLogForm * userLog;
    userInfoForm *userInfo;

    troubleLogForm * trouble;

    userManagementForm * sysAdmin;

    company_About * about ;

    LoginDialog * login;

    bool windowMoverControl;

    bool maxOrNormalCurrentStatus;

    bool isLeftPressDown;
    QPoint dragPosition;
    Direction dir;

    bool loginState;

    faultSearchDialog *faultSearch;

    //Ntp
    NtpClient * ntpClient;


};

#endif // MAINWINDOW_H
