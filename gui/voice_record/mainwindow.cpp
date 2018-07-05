#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("E:\\nowWork\\FromZero\\Test_Protocol\\Qt_P\\voice_record\\tttt.bin");
    file.open(QIODevice::ReadOnly);
    QByteArray fileArray =  file.readAll();
    qDebug()<<"file length:"<<fileArray.length();
    qDebug()<<QString::fromLocal8Bit("读取文件:")<<fileArray;
    qDebug()<<"SS"<<fileArray.toHex();



     VOICE_RECORD_TEXT = fileArray;
//    VOICE_RECORD_TEXT = "bbcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefgh";
    this->setWindowTitle(QString::fromLocal8Bit("语音记录仪模拟器(127.0.0.1)"));
    status = false;
    num = 0;

   server = new QTcpServer;
   server->setProxy(QNetworkProxy::NoProxy);

    bool status = server->listen(QHostAddress::LocalHost,7002);

    if(!status)
        qDebug()<<"Listen error";

    socket = new QTcpSocket;

    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    setCmd802R();
    setCmd803C();

  //  setCmd806C();
    setCmd807C();

    //skey
    skey[0] = 1;
    skey[1] = 2;
    skey[2] = 3;
    skey[3] = 4;

    //rkey
    rkey[0] = 5;
    rkey[1] = 6;
    rkey[2] = 7;
    rkey[3] = 8;


   //测试  用语测试 新协议





}

void MainWindow::acceptConnection()
{
    ui->textEdit->append(QString::fromLocal8Bit("新连接"));
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(my_Receive()));
    num += 1;
    ui->label_2->setText(QString::number(num));

}




void MainWindow::my_Receive()
{
    QHostAddress * hostAddress = new QHostAddress();
    QHostAddress hAddress = socket->peerAddress();
    qDebug()<<"hAddress:"<< hAddress.toString();
    QByteArray recBuff = socket->read(socket->bytesAvailable());
    qDebug()<<"recBuff:"<<recBuff;

    msg_Analysis(recBuff);
}


//解析  当要传送的数据大于8K的时候  就要考虑 发送者是分几次发送来的  （发送者主动发送次数哦 不是指 socket自动分包的次数哦）
void MainWindow::msg_Analysis(QByteArray &arec)
{
    qDebug()<<sizeof(int);
    int r_id = byteHexToInt(arec,sizeof(int)*2);//先解析第三个字段 确定消息类型//8
    qDebug()<<"msg_type"<<r_id;

      if(r_id == 800)
      {
          int length = byteHexToInt(arec,0);
          QByteArray Text = arec.mid(sizeof(int)*4);
          ui->textEdit->append(QString::fromLocal8Bit("消息长度")+QString::number( length));
          ui->textEdit->append(QString::fromLocal8Bit("明文：")+Text);

          //记录仪适用skey加密

          {
              //使用MD5源码文件生成
              //QString serverMD5Result32 = getMD5Result(Text,skey);//获取定制md5摘要32位长
              //QString serverMD5Result16 = serverMD5Result32.mid(8,16);//16位长
          }
           QByteArray QtMD532 =  QCryptographicHash::hash(Text,QCryptographicHash::Md5);
           qDebug()<<"MD5:"<<QtMD532;
          setCmd801R(QtMD532);

          ui->textEdit->append(QString::fromLocal8Bit("服务器明文生成的摘要32位:"));
          ui->textEdit->append(QtMD532);
//          ui->textEdit->append(QString::fromLocal8Bit("服务器明文生成的摘要16位:"));
//          ui->textEdit->append(serverMD5Result16);
          //记录仪发送回MD5认证
          ui->textEdit->append(QString::fromLocal8Bit("发送801R完成："));
          ui->textEdit->append(QString::fromLocal8Bit("801R指令:"));
          ui->textEdit->append(M_801R.toHex());

          //将生成密钥和记录仪明文发送回服务器  服务器对比摘要正确性
          socket->write(M_801R);
//          system("pause");

      }
      if(r_id == 801)
      {
          int length = byteHexToInt(arec,0);
//          QByteArray Text = arec.mid(sizeof(int)*4);//时间
          QString time = arec.mid(16,17);
          QString voiceRecordMD5 = arec.mid(37,16);
          ui->textEdit->append(QString::fromLocal8Bit("消息长度")+QString::number( length));
          ui->textEdit->append(QString::fromLocal8Bit("时间：")+time);
          ui->textEdit->append(QString::fromLocal8Bit("rkey生成的记录仪MD5:")+voiceRecordMD5);
          //验证rkey的正确性
           int ret = verifySkey(localRkeyMD5(),voiceRecordMD5);//验证本地的md5和记录仪经过skey后发回来的md5
           if(ret)
           {
                ui->textEdit->append(QString::fromLocal8Bit("服务器rkey正确性验证成功"));
           }
      }


      if(r_id == 802)//查询
      {
          int length = byteHexToInt(arec,0);
        //  QString nowTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss000");//时间格式测试
        //  qDebug()<<time;
          int channel = byteHexToInt(arec,sizeof(int)*3);
          QString startTime = arec.mid(20,37);
          QString endTime = arec.mid(41);
          ui->textEdit->append(QString::fromLocal8Bit("消息长度")+QString::number(length)+QString::fromLocal8Bit("频道;")+QString::number(channel));
          ui->textEdit->append(QString::fromLocal8Bit("开始时间:") +startTime);
          ui->textEdit->append(QString::fromLocal8Bit("结束时间:") +endTime);

          //802 result
            socket->write(M_802R);

          //803
          socket->write(M_803C);
          qDebug()<<QString::fromLocal8Bit("发送803")<<M_803C;

      }else if(r_id ==804 )
      {//第五个是偏移量
           int position = byteHexToInt(arec,sizeof(int)*4);
           qDebug()<<QString::fromLocal8Bit("音频请求位置偏移量:")<<position;
             //发送805告诉服务器接下来的语音文件有多大
          //806 音频数据传送因为中途有中断的请求
// 有蹦蹦蹦的声音  时有时没有
          QString fileName = record_FileList.at(position).fileName();
          QString deviceVoiceDir = voiceDirPath + "/";
          QString selectFileName = deviceVoiceDir +fileName;

          qDebug()<<"selectFileName:"<<selectFileName;
            QFile F(selectFileName);
            F.open(QIODevice::ReadOnly);
            int length = F.size();
            qDebug()<<"length:"<<length;

            setCmd805C(length);
            socket->write(M_805C);//传送音频启示信号和接下来的语音文件的大小

            while(!F.atEnd())
            {
                if(socket->waitForBytesWritten())
                {
                    QByteArray tmpM_Text = F.read(800);//800最大 一帧 512  Qt中socket的缓冲区默认设置为8k 所以 得保证 一帧是2的N次幂 496大小完美
                    this->SetPackageMD5(tmpM_Text.toStdString());
                    setCmd806C(tmpM_Text);
                    socket->write(M_806C);//音频数据
                }
            }
            F.close();

            std::vector<std::string>all_packeg_md5 =  this->GetallPackageMD5();

            std::string filename = "E:\\nowWork\\LSX_Management_system\\protocol_V\\Protocol\\LOG\\md5_send.txt";

            this->SetTXTMD5(all_packeg_md5,filename);


          if(socket->waitForBytesWritten())
          {
              socket->write(M_807C);//音频传送结束信号
          }
      }else if(r_id == 808)//停止传送音频信号  通知音频传送线程停止
      {
            ui->textEdit->append(QString::fromLocal8Bit("音频传送停止命令"));
            ui->textEdit->append(arec);
      }else if(r_id == 809)
      {
          ui->textEdit->append(QString::fromLocal8Bit("心跳包"));
      }


    //****************************************************
    //服务器解析
  /*  if(r_id == 802)//返回查询内容
    {
        ui->textEdit_2->append(QString::fromLocal8Bit("解析802r："));
        int record_Num = byteHexToInt(arec,sizeof(int)*3);
        ui->textEdit_2->append(QString::fromLocal8Bit("记录条数：")+QString::number(record_Num));
        for(int i =0;i<record_Num;i++)
        {
            QByteArray record_StartTime = arec.mid(sizeof(int)*4 +21*i,17);
            int record_Length = byteHexToInt(arec,sizeof(int)*4 + 17 + 21*i);
            ui->textEdit_2->append(QString::fromLocal8Bit("==========第")+QString::number(i+1)+QString::fromLocal8Bit("条："));
            ui->textEdit_2->append(QString::fromLocal8Bit("起始时间：")+record_StartTime);
            ui->textEdit_2->append(QString::fromLocal8Bit("本条记录长度：")+QString::number(record_Length));
        }
        int CID_StringLength = byteHexToInt(arec,sizeof(int)*4 +record_Num*21);
        QByteArray CID_String = arec.mid(sizeof(int)*4 +record_Num*21+sizeof(int));//本部分可从math上优化代码提高性能 v2.0
        ui->textEdit_2->append(QString::fromLocal8Bit("CID字符串长度：")+QString::number(CID_StringLength));
        ui->textEdit_2->append(QString::fromLocal8Bit("CID字符串：")+CID_String);

    }else if(r_id == 803)//查询发送结束信号
    {
        ui->textEdit_2->append(QString::fromLocal8Bit("收到查询结束信号"));
    }else if(r_id == 805)//通知发送语音是否成功信号
    {
       int check_Result = byteHexToInt(arec,sizeof(int)*3) ;
       int check_VoiceLength = byteHexToInt(arec,sizeof(int)*4);//该消息中记录额长度备用 用语确认 806发送的消息的正确性 有点相当于常用的校验位
        qDebug()<<"check_Result"<<check_Result;
        qDebug()<<"check_VoiceLength"<<check_VoiceLength;
       if(check_Result)
       {
            ui->textEdit_2->append(QString::fromLocal8Bit("查询语音消息成功"));
       }else
           ui->textEdit_2->append(QString::fromLocal8Bit("查询语音消息失败"));
    }else if(r_id == 806)//开始发送语音数据
    {
            int data_Length = byteHexToInt(arec,sizeof(int)*3);
            ui->textEdit_2->append(QString::fromLocal8Bit("语音长度")+QString::number(data_Length));
            qDebug()<<"data_Length"<<data_Length;
            QByteArray data_Voice =  arec.mid(sizeof(int)*4);
            ui->textEdit_2->append(QString::fromLocal8Bit("语音消息："));
            //ui->textEdit_2->append(data_Voice.toHex());
            ui->textEdit_2->append(data_Voice);
    }else if(r_id == 807)
    {
        ui->textEdit_2->append(QString::fromLocal8Bit("传送结果："));
        int transfer_Type = byteHexToInt(arec,sizeof(int)*3);
        qDebug()<<"transfer_Type"<<transfer_Type;
        if(transfer_Type)
            ui->textEdit_2->append(QString::fromLocal8Bit("正常结束"));
        else
            ui->textEdit_2->append(QString::fromLocal8Bit("异常结束"));
    }*/


}


void MainWindow::setCmd802R()//使用8条数据测试
{
    //8条
    QByteArray text = "helloworld";

    record_FileList = getReplyData();//获取本地
    int record_Num =record_FileList.size();//本来是用来模拟记录仪搜索本地语音记录的
    int length_HowMany = record_Num*21;//一共搜索到多少条记录的长度，每一条长度21
    qDebug()<<"length_HowMany"<<length_HowMany;

    M_802R = intToByteHex(330+length_HowMany)+intToByteHex(1)+intToByteHex(802)+intToByteHex(record_Num);

    qDebug()<<"fileSize:"<<record_Num;
    QString fileName = record_FileList.at(0).fileName();
    qDebug()<<"file"<<fileName;
    int fileSize = record_FileList.at(0).size();
    qDebug()<<"fileSize:"<<fileSize;

    for(int i = 0;i<record_Num;i++)
    {
        QByteArray nowTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss000").toLatin1();//测试用的当前时间
        int record_Length_Second = record_FileList.at(i).size()*(4-0.1752988) / 16000 ;//这是在查字节错误的时候得出的计算pcm文件大小的方程式，文件播放大小可以用录音结束时间减去录音开始时间得出（802）
        M_802R = M_802R+nowTime+intToByteHex(record_Length_Second);
    }
    M_802R = M_802R +intToByteHex(310);

    for(int i =0;i<31;i++)//模拟310长度的字符串
    {
        M_802R = M_802R + text;
    }
    qDebug()<<"802R:"<<M_802R;
    //qDebug()<<"Length:"<<
}

QFileInfoList MainWindow::getReplyData()//返回搜索本地语音目录的一个QFileInfoList
{
    QString strAppPath = QCoreApplication::applicationDirPath();
    qDebug()<<strAppPath;
    voiceDirPath = strAppPath + "/voice";
    QDir voiceDir =QDir(voiceDirPath);
    QFileInfoList fileList = voiceDir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    int fileSize = fileList.size();
    qDebug()<<"fileSize:"<<fileSize;
    return fileList;
}

void MainWindow::setCmd803C()
{
    M_803C = intToByteHex(12)+intToByteHex(0)+intToByteHex(803);
    qDebug()<<"803Length:"<<strlen(M_803C);
    qDebug()<<"Msg:"<<M_803C;
}

void MainWindow::setCmd805C(int musicLength)
{
    M_805C = intToByteHex(20)+intToByteHex(0)+intToByteHex(805)+intToByteHex(1)+intToByteHex(musicLength);
    qDebug()<<QString::fromLocal8Bit("M_805C消息:")<<M_805C;
}

void MainWindow::setCmd806C(QByteArray tmp_Text)//消息
{
    QByteArray Text = "hello";
    M_806C = "";
    M_806C = intToByteHex(16+tmp_Text.length())+intToByteHex(0)+intToByteHex(806)+intToByteHex(tmp_Text.length())+tmp_Text;
    ui->textEdit->append(M_806C.toHex());
    ui->textEdit->append("""******************");
}

void MainWindow::setCmd807C()
{
    M_807C = intToByteHex(16)+intToByteHex(0)+intToByteHex(807)+intToByteHex(1);//1：正常结束 2：异常结束
}






void MainWindow::sleepTime()
{
    status = true;
    qDebug()<<"sleepTimeOut";
}




QByteArray MainWindow::intToByteHex(int number)//大端 网络字节序
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[3] = (uchar)  (0x000000ff & number);
    abyte0[2] = (uchar) ((0x0000ff00 & number) >> 8);
    abyte0[1] = (uchar) ((0x00ff0000 & number) >> 16);
    abyte0[0] = (uchar) ((0xff000000 & number) >> 24);
    return abyte0;
}


/*
 * int position: 是为解析消息方便引入的  解析个字段到strings
*/
int MainWindow::byteHexToInt(QByteArray arry, int postion)//big 大端 网络字节序
{
    int value;
    value = (int)((arry[postion+3] & 0xFF)
        | ((arry[postion + 2] << 8) & 0xFF00)
        | ((arry[postion + 1] << 16) & 0xFF0000)
        | ((arry[postion + 0] << 24) & 0xFF000000));
    return value;
}


void MainWindow::delay(int second)
{

    QTime t;
    t.start();
    while(t.elapsed()<50*second)
    QCoreApplication::processEvents();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::delObj()
{

}





void MainWindow::on_pushButton_clicked()
{
    arry = new QByteArray;
     arry->resize(1000);
}

void MainWindow::on_pushButton_2_clicked()
{
    delete arry;
}

void MainWindow::on_pushButton_3_clicked()
{
//    socket->disconnected();
    socket->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    num = 0;
    ui->label_2->setText("0");
    ui->textEdit->clear();
}

void MainWindow::setCmd801R(QByteArray QtMD532)
{
    qDebug()<<"QtMD532:"<<QtMD532.toHex();
    M_801R = intToByteHex(164)+intToByteHex(0)+intToByteHex(801)+intToByteHex(16)+QtMD532+intToByteHex(128)+VOICE_RECORD_TEXT;

}

QString MainWindow::getMD5Result(QString Text, uint4 key[])
{
    MD5 serverMD5(Text.toStdString(),key);
    return QString::fromStdString(serverMD5.md5());
}




bool MainWindow::verifySkey(QString localMD5,QString rkeyMD5)//localMD5:
{
    if(localMD5 == rkeyMD5)
        return 1;

    return 0;
}


QString MainWindow::localRkeyMD5()
{
    MD5 voiceRecordMD5(VOICE_RECORD_TEXT.toStdString(),rkey);
    QString localRkeyMD5_32 = QString::fromStdString(voiceRecordMD5.md5());
    qDebug()<<QString::fromLocal8Bit("本地MD5_32:")<<localRkeyMD5_32;
    ui->textEdit->append(QString::fromLocal8Bit("本地MD5_32: ") + localRkeyMD5_32);
    QString localRkeyMD5_16 = localRkeyMD5_32.mid(8,16);//16位长
    qDebug()<<QString::fromLocal8Bit("本地MD5:")<<localRkeyMD5_16;
    ui->textEdit->append(QString::fromLocal8Bit("本地MD5_16: ") + localRkeyMD5_16);
    return localRkeyMD5_16;
}

