#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <fstream>
#include <vector>

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFileInfoList>
#include <QNetworkProxy>
#include "md5.h"
#include <QCryptographicHash>

typedef unsigned int uint4;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void sleepTime();
    void acceptConnection();
    void my_Receive();


    void Write(std::string str,std::string filename)
    {
        std::ofstream ofs(filename,std::ios::app);
        if(ofs.is_open())
        {
            ofs.write(str.data(),str.length());
            ofs.write("\n",1);
            ofs.close();
        }
    }

    void SetPackageMD5(std::string text)
    {
        this->md5.update(text.c_str(), text.length());
        this->md5.Set_finalized_Inti_Status();
        this->md5.finalize();
        std::string md5_str =  this->md5.md5();
        package_md5.push_back(md5_str);
       // qDebug()<<"md5_str:"<<md5_str;
    }
    std::vector<std::string> GetallPackageMD5()
    {
        return package_md5;
    }
    void SetTXTMD5(std::vector<std::string> &vec,std::string filename)
    {
        std::string str;

        std::ofstream file(filename);
        if (file.is_open())
        {
            file.close();
            remove(filename.c_str());
        }//clean the file

        std::ofstream ofs(filename,std::ios::app);
        if(ofs.is_open())
        {
            std::vector<std::string>::iterator it = vec.begin();
            std::string package = "MD5 for each packet:";
            ofs.write(package.data(),package.length());
            ofs.write("\n",1);
            for(;it != vec.end();it++)
            {
                ofs.write((*it).data(),(*it).length());
                ofs.write("\n",1);
                str = str + (*it) ;
            }
            this->md5.update(str.c_str(), str.length());
            this->md5.Set_finalized_Inti_Status();
            this->md5.finalize();
            std::string md5_str =  this->md5.md5();
            std::string txt = "MD5 generated using the MD5 sum of each packet:";
            ofs.write(txt.data(),txt.length());
            ofs.write("\n",1);
            ofs.write(md5_str.data(),md5_str.length());
            ofs.write("\n",1);

            ofs.close();
         }
    }

public:
    void delay(int second);
    int byteHexToInt(QByteArray arry, int postion);
    QByteArray intToByteHex(int number);//大端 网络字节序
    void msg_Analysis(QByteArray &arec);
    void setCmd801R(QByteArray QtMD532);//回复调听服务器md5认证消息
    void setCmd802R();
    void setCmd803C();
    void setCmd805C(int);
    void setCmd806C(QByteArray);
    void setCmd807C();
    bool verifySkey(QString localMD5,QString skeyMD5);//localMD5:
    QString localRkeyMD5();

    QString getMD5Result(QString Text, uint4 key[4]);


    void delObj();

    QFileInfoList getReplyData();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
     QTcpServer * server;
     QTcpSocket * socket;

     //消息
     QByteArray M_801R;
     QByteArray M_803C;
     QByteArray M_802R;
     QByteArray M_805C;
     QByteArray M_806C;
     QByteArray M_807C;


     bool status;

     QByteArray * arry;
     QFileInfoList record_FileList;
     QString voiceDirPath;
     int num;

     QByteArray VOICE_RECORD_TEXT;

      uint4 skey[4];
      uint4 rkey[4];

      std::vector<std::string>package_md5;
      MD5 md5;

};

#endif // MAINWINDOW_H
