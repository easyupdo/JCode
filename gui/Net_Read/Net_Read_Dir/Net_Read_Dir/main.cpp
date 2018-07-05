#include "mainwindow.h"
#include <QApplication>
//#include "vld.h"

void setStyle(const QString &StyleName)
{
//    QString AppPath = QCoreApplication::applicationDirPath();
//    QString QssPath = AppPath + QString::fromLocal8Bit("/image/qss/%1.css").arg(StyleName);
//    qDebug()<<QString::fromLocal8Bit("qss路径:")<<QssPath;
    QFile file(StyleName);
    int status = file.open(QFile::ReadOnly);
    qDebug()<<"status"<<status;
    QString qss = QLatin1String(file.readAll());

    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    setStyle(":/Resources/blue123.css");
    qDebug()<<"Sytle set over ok!";
    w.show();
    w.setFocusPolicy(Qt::WheelFocus);


//    for(int i = 0;i<100;i++)
//    {
//        PhoneticDialog *phonetic = new PhoneticDialog;
//        phonetic->show();

//    }


    return a.exec();
}
