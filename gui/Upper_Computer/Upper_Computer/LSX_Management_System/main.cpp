#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "app/global.h"

#ifdef _DEBUG
#include <vld.h>
#endif

#define QT_DEBUG



static FILE *q_fileStream = NULL;
#define _TIME_ qPrintable(QTime::currentTime().toString("hh:mm:ss:zzz"))


//Log 处理程序 全局
static void SoftWareShutDown ()
{
    if (NULL != q_fileStream)
    {
        qDebug("Close log file.");
        fclose (q_fileStream);
        q_fileStream = NULL;
    }
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf (q_fileStream, "%s: %s (%s:%u, %s)\n", _TIME_, localMsg.constData(), context.file, context.line, context.function);
        fflush (q_fileStream);
        //qDebug()<<"localMsg.constData:"<<localMsg.constData()<<context.file<<context.line<<context.function;
        break;
    case QtInfoMsg:
        fprintf (q_fileStream, "%s: %s (%s:%u, %s)\n", _TIME_, localMsg.constData(), context.file, context.line, context.function);
        fflush (q_fileStream);
        break;
    case QtWarningMsg:
        fprintf (q_fileStream, "%s: %s (%s:%u, %s)\n", _TIME_, localMsg.constData(), context.file, context.line, context.function);
        fflush (q_fileStream);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}



static void installMsgHandler(QString strLogFile)
{
    QByteArray byteArrayLogFile = strLogFile.toLatin1();
    qInstallMessageHandler(myMessageOutput);

    if (NULL != q_fileStream)
    {
        fclose (q_fileStream);
        q_fileStream = NULL;
    }

    q_fileStream = fopen (byteArrayLogFile.constData (), "w+");//w+ 每次重启 重写log
    if (NULL != q_fileStream)
    {
        qDebug("Opened log file.");
    }
    else
    {
        qDebug("Failed to open log file.");
    }
}

static void installReleaseMsgHandler ()
{
    QString strAppPath = QCoreApplication::applicationDirPath();
    QString strLogFile = strAppPath + "/log" + "/log.txt";
    qDebug()<<"LogFilePath:"<<strLogFile;
    installMsgHandler (strLogFile);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    global  styleGlobal;
    styleGlobal.setStyle("blue123");//全局控件样式
#ifdef QT_DEBUG // release 版本log控制
    bool bAddQuitFunc = false;
                qDebug()<<"TTTTTTTTTTTTTT";
    installReleaseMsgHandler();

    if (!bAddQuitFunc)
    {
        qAddPostRoutine (SoftWareShutDown);
        bAddQuitFunc = true;
    }
#endif

//    int ret = -1;
//    do
//    {
//        LoginDialog * login = new LoginDialog();
//        login->show();
//        ret = a.exec();
//    }while(ret != 0);   //这种一直在事件循环中 重启  会导致 内存不释放 重启 分配内存  造成内存浪费    可以Qprocess重启外部程序

    MainWindow  mainwindow;
    mainwindow.show();
    mainwindow.reBootLoginDialog();

    return a.exec();
}
