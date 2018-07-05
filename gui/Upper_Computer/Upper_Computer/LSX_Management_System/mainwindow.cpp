#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QDateTime>
#include <QTimer>
#include <QMouseEvent>
#include "devicecontrolform.h"

#include <QGridLayout>
#include "ui_devicecontrolform.h"
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QtSql/QSqlDatabase>
#include "app/global.h"
#include "adduserform.h"
#include "userinfoform.h"
#include "troublelogform.h"
#include "sysmanagementform.h"
#include <QPicture>
#include <QPixmap>
#include<Windows.h>
#include <windowsx.h>
#include "logindialog.h"
#include "app/imessagebox.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/monitor.ico"));

   // this->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint |Qt::WindowMinMaxButtonsHint);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->label_Title->setMouseTracking(true);
    ui->widget->setMouseTracking(true);
    ui->statusBar->setMouseTracking(true);
    ui->widget_title->setMouseTracking(true);

    ui->label->setPixmap(QPixmap(":/image/blue_home_white.png"));

    maxOrNormal = true;//设置初始状态的大小
    windowsMove = true;
    windowMoverControl = false;
    maxOrNormalCurrentStatus = false;
    loginState = false;
    ui_width = MainWindow::width();//获取界面的宽度
    ui->statusBar->setMaximumHeight(10);
    this->setWindowTitle(QString::fromLocal8Bit("铁路语音记录仪监控管理系统"));


//    company->setText(QString::fromLocal8Bit("凌声芯语音科技有限公司"));
//    statusBar()->setStyleSheet(QString("QStatusBar::item{border:0px}"));//去掉label的边框.

//    ui->statusBar->addWidget(company);
    QDesktopWidget* desktopWidget = QApplication::desktop();//获取设备屏幕大小
    QRect screenRect = desktopWidget->screenGeometry();
    desk_width = screenRect.width();


    ui->toolBox->setItemText(0,QString::fromLocal8Bit("设备中心"));
    ui->toolBox->setItemText(1,QString::fromLocal8Bit("用户中心"));
    ui->toolBox->setItemText(2,QString::fromLocal8Bit("系统设置"));



//    QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
//    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);

    QIcon minIcon = QIcon(":/image/min.png");
    ui->minButton->setIcon(minIcon);

    ui->minButton->setIcon(minIcon);
    ui->maxButton->setIcon(QIcon(":/image/max.png"));
    ui->closeButton->setIcon( QIcon(":/image/close.png"));


    //注册双击要监测的对象
    ui->label_Title->installEventFilter(this);


    //Time
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(showCurrentTime()));
    timer->start(1000);


   // deviceControl->ui->tableView->setModel(mysql->sqlModel);

    //mysql init 数据库
    mysql = new MysqlSupport(this);


    //设备控制ui
    deviceControl = new DeviceControlForm();
    ui->stackedWidget->insertWidget(1,deviceControl);

    connect(this,SIGNAL(toDeviceControl(QString)),deviceControl,SLOT(fromMainWindow(QString)));
    connect(this,&MainWindow::toDeviceControlForSaveInfo,deviceControl,&DeviceControlForm::fromMainWindowForSaveInfo);


    //设备巡查ui
    devicePolling = new DevicePollingForm(this);
    ui->stackedWidget->insertWidget(2,devicePolling);
    connect(this,&MainWindow::toDevicePollingForAccessControl,devicePolling,&DevicePollingForm::fromMainWindowForAccessControl);

    connect(devicePolling,&DevicePollingForm::toMainWindowForDeviceInfo,this,&MainWindow::fromPollingForDeviceInfo);
    connect(this,&MainWindow::toDeviceControlForDeviceInfo,deviceControl,&DeviceControlForm::fromMainWindowForDeviceInfo);





    //设备管理ui
    deviceManagement = new DeviceManagementForm(this);
    ui->stackedWidget->insertWidget(3,deviceManagement);
    connect(this,&MainWindow::toDeviceManagementForAccessControl,deviceManagement,&DeviceManagementForm::fromMainWindowForAccessControl);

    //日志ui
    userLog = new userLogForm(this);
    ui->stackedWidget->insertWidget(4,userLog);

     //用户信息ui
     userInfo = new userInfoForm(this);
     ui->stackedWidget->insertWidget(5,userInfo);
     connect(this,SIGNAL(toUserInfo(QString)),userInfo,SLOT(fromMainWindow(QString)));
     connect(userInfo,&userInfoForm::toLoginDialogForReLogin,this,&MainWindow::fromUserInfoForReLogin);

     //故障信息
     trouble = new troubleLogForm(this);
    ui->stackedWidget->insertWidget(6,trouble);

    //sys管理
    sysAdmin = new userManagementForm(this);
    ui->stackedWidget->insertWidget(7,sysAdmin);
    connect(sysAdmin,SIGNAL(changeVoiceDownRootDir(QString)),this,SLOT(fromSysAdmin(QString)));
    //about
    about = new company_About(this);
    ui->stackedWidget->insertWidget(8,about);

    //faultSearch
    faultSearch = new faultSearchDialog(this);
    ui->stackedWidget->insertWidget(9,faultSearch);

    connect(this,&MainWindow::toDeviceFaultSearchForDeviceInfo,faultSearch,&faultSearchDialog::fromMainWindowForDeviceInfo);

    //NTP
    ntpClient = new NtpClient;
    connect(ntpClient,&NtpClient::replyReceived,this,&MainWindow::onReplyReceived);
    ntpClient->sendRequest(QHostAddress("202.112.31.197"),123);




}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::btn_place()
{
    ui->minButton->setGeometry(wid-67,5,20,20);
    ui->maxButton->setGeometry(wid-46,5,20,20);
    ui->closeButton->setGeometry(wid-25,5,20,20);
}

void MainWindow::on_minButton_clicked()
{
    if( windowState() != Qt::WindowMinimized )
    {
        setWindowState( Qt::WindowMinimized );
    }
}

void MainWindow::on_maxButton_clicked()
{
    qDebug()<<"maxOrNormal"<<maxOrNormal;
    QIcon icon;
    if( maxOrNormal )//最大化
    {
//        icon = style()->standardIcon( QStyle::SP_TitleBarNormalButton );
        ui->maxButton->setIcon(QIcon(":/image/max-min2.png"));
        setWindowState( Qt::WindowMaximized );
        maxOrNormalCurrentStatus = true;
        qDebug()<<QString::fromLocal8Bit("最大化");
    }
    else//常规大小
    {
        //wid =Widget::width();//获取界面的宽度
      //  wid = ui_width;
//        icon = style()->standardIcon( QStyle::SP_TitleBarMaxButton );
//        ui->maxButton->setIcon(icon);

        QIcon minIcon = QIcon(":/image/max.png");
        ui->maxButton->setIcon(minIcon);
        qDebug()<<ui->maxButton->size();
        setWindowState( Qt::WindowNoState );
        maxOrNormalCurrentStatus = false;
        qDebug()<<QString::fromLocal8Bit("最小化");

    }
    maxOrNormal = !maxOrNormal;
    btn_place();//设置按钮位置
}

void MainWindow::on_closeButton_clicked()
{
    emit toDeviceControlForSaveInfo();//关闭前先让主窗口保存该保存的文件//config.int 中DistanceVolume字段
    close();
    qApp->closeAllWindows();
}


void MainWindow::showCurrentTime()
{
    QDateTime nowTime = QDateTime::currentDateTime();
    QString str = nowTime.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->currentTime->setText(str);
}




//监测对象
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick)//双击
    {
        if(maxOrNormalCurrentStatus ==false)// if the window is little
        {
            maxOrNormal = true;
          //  windowsMove = true;
            this->on_maxButton_clicked();               //最大化或者恢复
        }else
        {
            maxOrNormal = false;
            this->on_maxButton_clicked();
        }
        return true;
    }

   if (event->type() == QEvent::MouseButtonPress)//单击
   {
       maxOrNormal = true;
       qDebug()<<"mousePress";
        windowMoverControl = true;

      //  if(this->pos())
   }
    return QObject::eventFilter(obj, event);
}


//鼠标单机事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

        mousePoint = event->globalPos() - this->pos();
        event->accept();
        isLeftPressDown = true;
        if(dir != NONE) {
            this->mouseGrabber();
        } else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(maxOrNormalCurrentStatus == true)
    maxOrNormal = false;
    else
        maxOrNormal = true;
    windowMoverControl = false;
    qDebug()<<"Release"<<maxOrNormal;

    isLeftPressDown = false;
    if(dir != NONE) {
        this->releaseMouse();
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

//鼠标移动事件  窗体移动
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug()<<"windowMoverControl:"<<windowMoverControl;
    if(maxOrNormalCurrentStatus == true)
        windowMoverControl =false;
    if ((event->buttons()) && windowMoverControl)
    {
        this->move(event->globalPos() - mousePoint);
        event->accept();
    }

    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isLeftPressDown) {
        this->region(gloPoint);
    } else {

        if(dir != NONE) {
            QRect rMove(tl, rb);

            switch(dir) {
            case LEFT:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());
                break;
            case UP:
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case LEFTTOP:
                if(rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if(rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setY(gloPoint.y());
                break;
            case LEFTBOTTOM:
                rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            default:

                break;
            }
            this->setGeometry(rMove);
        } else {
         //   move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
}
void MainWindow::region(const QPoint &cursorGlobalPoint)
{
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());
    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + PADDING && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - PADDING) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + PADDING){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - PADDING) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(loginState)
    {
    ui->stackedWidget->setCurrentIndex(1);

    {
        ui->label_2->setText(">>");
        ui->label_3->setText("");
        ui->label_4->setText("");
        ui->label_5->setText("");
        ui->label_10->setText("");
        ui->label_7->setText("");
        ui->label_8->setText("");
        ui->label_4->setText("");
    }

    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("请先登录"),"prompt");
        box.exec();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(loginState)
    {
    ui->stackedWidget->setCurrentIndex(2);
    //测试
//    deviceControl->show();
    qDebug()<<QString::fromLocal8Bit("巡检按钮");
    qDebug()<<QString::fromLocal8Bit("巡检按钮结束");

    {
        ui->label_2->setText("");
        ui->label_3->setText(">>");
        ui->label_4->setText("");
        ui->label_5->setText("");
        ui->label_10->setText("");
        ui->label_7->setText("");
        ui->label_8->setText("");
        ui->label_4->setText("");
    }

    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("请先登录"),"prompt");
        box.exec();
    }
}



void MainWindow::on_pushButton_11_clicked()
{
    if(loginState)
    {
    ui->stackedWidget->setCurrentIndex(3);

    {
        ui->label_2->setText("");
        ui->label_3->setText("");
        ui->label_4->setText(">>");
        ui->label_5->setText("");
        ui->label_6->setText("");
        ui->label_9->setText("");
        ui->label_8->setText("");
        ui->label_10->setText("");
    }

    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("请先登录"),"prompt");
        box.exec();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(loginState)
    {
    ui->stackedWidget->setCurrentIndex(8);

    {
        ui->label_2->setText("");
        ui->label_3->setText("");
        ui->label_4->setText("");
        ui->label_5->setText("");
        ui->label_6->setText("");
        ui->label_9->setText("");
        ui->label_8->setText("");
        ui->label_10->setText(">>");
    }

    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("请先登录"),"prompt");
        box.exec();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_6_clicked()
{
     ui->stackedWidget->setCurrentIndex(7);

}



void MainWindow::on_pushButton_8_clicked()
{
    if(loginState)
    {
    ui->stackedWidget->setCurrentIndex(4);

    {
        ui->label_2->setText("");
        ui->label_3->setText("");
        ui->label_4->setText("");
        ui->label_5->setText("");
        ui->label_6->setText("");
        ui->label_8->setText("");
        ui->label_9->setText(">>");
        ui->label_10->setText("");
    }

    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("请先登录"),"prompt");
        box.exec();
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    if(loginState)
    {
    ui->stackedWidget->setCurrentIndex(5);
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->label_6->setText(">>");
    ui->label_8->setText("");
    ui->label_9->setText("");
    ui->label_10->setText("");

     emit toUserInfo(ui->label_UserName->text());
    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("请先登录"),"prompt");
        box.exec();
    }

}


void MainWindow::fromLoginDialog(QString string,bool userType)
{
    //主窗口下栏登录信息显示
    qDebug()<<"string"<<string;
    ui->label_UserName->setText(string);//登录用户
//    if(!userType)//1:admin   0:public
//    {
       //普通用户
        emit  toDevicePollingForAccessControl(userType);
        emit toDeviceManagementForAccessControl(userType);
//    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(loginState)
    {
    {
        ui->label_2->setText("");
        ui->label_3->setText("");
        ui->label_4->setText("");
        ui->label_5->setText(">>");
        ui->label_10->setText("");
        ui->label_7->setText("");
        ui->label_8->setText("");
        ui->label_4->setText("");
    }
        ui->stackedWidget->setCurrentIndex(9);

    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("请先登录"),"prompt");
        box.exec();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if(loginState)
    {
    ui->stackedWidget->setCurrentIndex(7);

    {
        ui->label_2->setText("");
        ui->label_3->setText("");
        ui->label_4->setText("");
        ui->label_5->setText("");
        ui->label_10->setText("");
        ui->label_9->setText("");
        ui->label_8->setText(">>");
        ui->label_4->setText("");
    }

    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("请先登录"),"prompt");
        box.exec();
    }
}


void MainWindow::fromSysAdmin(QString string)
{
    qDebug()<<"stringAdmin----------:"<<string;
    emit this->toDeviceControl(string);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
   // qDebug()<<"TT++++++++++++++++++++++++++++++++++++++++++++++++";
    MSG* msg = (MSG*)message;
        switch(msg->message)
        {
        case WM_NCHITTEST:
            int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
            int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
            if(this->childAt(xPos,yPos) == 0)
            {
                *result = HTCAPTION;
            }else{
                return false;
            }
            if(xPos > 0 && xPos < 8)
                *result = HTLEFT;
            if(xPos > (this->width() - 8) && xPos < (this->width() - 0))
                *result = HTRIGHT;
            if(yPos > 0 && yPos < 8)
                *result = HTTOP;
            if(yPos > (this->height() - 8) && yPos < (this->height() - 0))
                *result = HTBOTTOM;
            if(xPos > 18 && xPos < 22 && yPos > 18 && yPos < 22)
                *result = HTTOPLEFT;
            if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > 18 && yPos < 22)
                *result = HTTOPRIGHT;
            if(xPos > 18 && xPos < 22 && yPos > (this->height() - 22) && yPos < (this->height() - 18))
                *result = HTBOTTOMLEFT;
            if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > (this->height() - 22) && yPos < (this->height() - 18))
                *result = HTBOTTOMRIGHT;
            return true;
        }
        return false;
}

void MainWindow::fromDeviceControl()
{
    qDebug()<<QString::fromLocal8Bit("信号来自DeviceControl !");
    emit toLoginDialog();
}

void MainWindow::reBootLoginDialog()
{
    qDebug()<<QString::fromLocal8Bit("重新登录操作");
//        qDebug()<<"RRRRR:"<<login->exec();
}

void MainWindow::fromUserInfoForReLogin()
{
    delete userInfo;
    //用户信息ui
    userInfo = new userInfoForm;
    ui->stackedWidget->insertWidget(5,userInfo);
    connect(this,SIGNAL(toUserInfo(QString)),userInfo,SLOT(fromMainWindow(QString)));
    connect(userInfo,&userInfoForm::toLoginDialogForReLogin,this,&MainWindow::fromUserInfoForReLogin);
    qDebug()<<QString::fromLocal8Bit("发送重登陆信号!");
    login->reBootControl();
    reBootLoginDialog();
}



void MainWindow::on_loginButton_clicked()
{
        //用户登录
    if(loginState)
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("您已登录系统!"),"prompt");
        box.exec();
    }else
    {
        login = new LoginDialog();
        connect(login,&LoginDialog::toMainWindow,this,&MainWindow::fromLoginDialog);
        connect(login,&LoginDialog::toMainWindowForLoginState,this,&MainWindow::fromLoginDialogForLoginState);
        connect(login,&LoginDialog::toDevicePollingForStartPolling,devicePolling,&DevicePollingForm::fromMainWindowForStartPolling);
        login->exec();
    }
}

void MainWindow::fromLoginDialogForLoginState(bool loginState)
{
    this->loginState = loginState;
}

void MainWindow::on_logoutButton_clicked()
{
    if(this->loginState)
    {
        this->loginState = false;
        ui->stackedWidget->setCurrentIndex(6);
        {
            ui->label_2->setText("");
            ui->label_3->setText("");
            ui->label_4->setText("");
            ui->label_5->setText("");
        }
        ui->label_UserName->setText(QString::fromLocal8Bit("未登录"));
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("您已退出系统 欢迎下次使用"),"prompt");
        box.exec();
    }else
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("您未登录系统"),"prompt");
        box.exec();
    }
}

//Ntp
void MainWindow::onReplyReceived(QHostAddress host, quint16 port, NtpReply reply)
{
    qDebug() <<QString::fromLocal8Bit("当前时间:");
    qDebug()<<QString::fromLocal8Bit("IP:")<<host.toIPv4Address()<<"Port:"<<port;
    qDebug()<<  reply.referenceTime();
    qDebug() << reply.originTime();

    qDebug() << QString::fromLocal8Bit("NTP指示器:")<<reply.leapIndicator();
    qDebug() << QString::fromLocal8Bit("NTP版本号:")<<reply.versionNumber();
    qDebug() << QString::fromLocal8Bit("NTP工作模式:")<<reply.mode();
    qDebug() << QString::fromLocal8Bit("NTP时钟层数:")<<reply.stratum();
    qDebug() << QString::fromLocal8Bit("NTP轮训时间:")<<reply.pollInterval();
    qDebug() << QString::fromLocal8Bit("NTP精度:")<<reply.precision();
    qDebug() << QString::fromLocal8Bit("NTP时钟最后设定时间:")<<reply.referenceTime();
    qDebug() << QString::fromLocal8Bit("NTP报文离开发送端时间:")<<reply.originTime();
    qDebug() << QString::fromLocal8Bit("NTP报文返回发送端时间:")<<reply.receiveTime();
    qDebug() << QString::fromLocal8Bit("NTP服务器离开服务器端时间:")<<reply.destinationTime();
    qDebug() << QString::fromLocal8Bit("NTP服务器离开到达目的地时间:")<<reply.transmitTime();

    qDebug() << QString::fromLocal8Bit("NTP往返延迟时间:")<<reply.roundTripDelay();
    qDebug() << QString::fromLocal8Bit("本地时间偏移量:")<<reply.localClockOffset();
}


void MainWindow::fromPollingForDeviceInfo(QString *string,bool pageType)
{
    switch(pageType)
    {
        case 1:
            ui->stackedWidget->setCurrentIndex(1);
            emit toDeviceControlForDeviceInfo(string);
            ui->label_2->setText(">>");
            ui->label_3->setText("");
            ui->label_4->setText("");
            ui->label_5->setText("");
            ui->label_10->setText("");
            ui->label_7->setText("");
            ui->label_8->setText("");
            ui->label_4->setText("");
        break;
        case 2:
            ui->stackedWidget->setCurrentIndex(9);
            emit toDeviceFaultSearchForDeviceInfo(string);
            ui->label_2->setText("");
            ui->label_3->setText("");
            ui->label_4->setText("");
            ui->label_5->setText(">>");
            ui->label_10->setText("");
            ui->label_7->setText("");
            ui->label_8->setText("");
            ui->label_4->setText("");
        break;

    }


}

