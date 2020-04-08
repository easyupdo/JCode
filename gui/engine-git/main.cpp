#include "mainwindow.h"
#include <QApplication>


static FILE *q_fileStream = NULL;
#define _TIME_ qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd:hh:mm:ss"))


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
    fprintf (q_fileStream, "%s: %s [%s] [%s:%u:%s]\n", _TIME_,"Debug:", localMsg.constData(), context.file, context.line, context.function);
    fflush (q_fileStream);
    qDebug()<<_TIME_;
    //qDebug()<<"localMsg.constData:"<<localMsg.constData()<<context.file<<context.line<<context.function;
    break;
  case QtInfoMsg:
    fprintf (q_fileStream, "%s: %s [%s] [%s:%u:%s]\n", _TIME_, "Info",localMsg.constData(), context.file, context.line, context.function);
    fflush (q_fileStream);
    break;
  case QtWarningMsg:
    fprintf (q_fileStream, "%s: %s [%s] [%s:%u:%s]\n","Warning", _TIME_, localMsg.constData(), context.file, context.line, context.function);
    fflush (q_fileStream);
    break;
  case QtCriticalMsg:
    fprintf(stderr, "Critical: [%s] [%s:%u:%s]\n", localMsg.constData(), context.file, context.line, context.function);
    break;
  case QtFatalMsg:
    fprintf(stderr, "Fatal: [%s] [%s:%u:%s]\n", localMsg.constData(), context.file, context.line, context.function);
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





int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  freopen( "CON", "w", stdout ); //输出到控制台"CON"

  bool bAddQuitFunc = false;
  qDebug()<<"TTTTTTTTTTTTTT";
  installReleaseMsgHandler();

  if (!bAddQuitFunc)
  {
    qAddPostRoutine (SoftWareShutDown);
    bAddQuitFunc = true;
  }

  MainWindow w;
  w.show();

  return a.exec();
}
