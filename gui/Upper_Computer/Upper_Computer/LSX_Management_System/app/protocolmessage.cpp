#include "protocolmessage.h"
#include <QCryptographicHash>
#include <QObject>
#include <QDir>
#include "adpcm2pcm.h"
#include "pcm2play.h"

ProtocolMessage::ProtocolMessage(QObject *parent):QObject(parent)
{
    voice_Length = 0;
    iTestCount = 0;
    check_VoiceLength = 0;
    check_TempLength = 0;
    test_allDataLength = 0;
    test_allPCMDataLength = 0;
    decodeDataLength = 0;
    PREVIndexRow = 0;
    sameWay = false;



    setDufaultVoiceDownDir();//设置默认语音下载目录


   // QCryptographicHash * newKey = new QCryptographicHash;
    text = "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefgh";
    QByteArray kText = text.toLatin1();
    QByteArray md5 =  QCryptographicHash::hash(kText,QCryptographicHash::Md5);
    qDebug()<<QString::fromLocal8Bit("Md5密钥:")<<md5.toHex();

    {
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
    }
    MD5 customMD5(text.toStdString(),skey);
    QString customMD5Result32 = QString::fromStdString(customMD5.md5());//32位
    qDebug()<<QString::fromLocal8Bit("定制的md5密钥32位:")<<customMD5Result32;
    QString customMD5Result16 = customMD5Result32.mid(8,16);
    qDebug()<<QString::fromLocal8Bit("定制的md5密钥16位:")<<customMD5Result16;

    setCmd800();
    setCmd802C();
    setCmd800();
    setCmd802C();
    //setCmd804C();
    setCmd808C();
    setCmd809C();

   // socket = new QTcpSocket;

   // socket->setSocketOption();

    //connect(socket,SIGNAL(readyRead()),this,SLOT(my_Receive()));

    To = new adpcm2Pcm;
    pcm2play *pcmPlayer = new pcm2play;
    pcmPlayer->initlayer();//初始化播放器参数
    connect(pcmPlayer,&pcm2play::toProtocolMessageSameMusicLangth,this,&ProtocolMessage::fromPcm2PlayForTellSameSelectMusicLength);
    connect(pcmPlayer,&pcm2play::toProtocolMessageMusicPlayOver,this,&ProtocolMessage::fromPcm2PlayForTellMusicPlayOver);



//    connect(timer, SIGNAL(timeout()),this, SLOT(timeOut()));
  //  timer->start(1000);
    connect(this,&ProtocolMessage::toPcmToPlay,pcmPlayer,&pcm2play::slotTimeout);//写入到播放缓冲区中的
    connect(this,&ProtocolMessage::toPcm2PlayOrPauseControl,pcmPlayer,&pcm2play::fromProtocolMessageForPlayOrPauseControl);
    connect(this,&ProtocolMessage::toPcm2PlayForClearAllBuffer,pcmPlayer,&pcm2play::fromProtocolMessageForClearAllBuffer);
    connect(this,&ProtocolMessage::toPcm2PalyForStopDistancePlay,pcmPlayer,&pcm2play::fromProtocolMessageForStopDistancePlay);
    connect(this,&ProtocolMessage::toPcm2PlayReceiveOver,pcmPlayer,&pcm2play::fromProtocolMessageReceiveOver);
//    connect();
    connect(this,&ProtocolMessage::toPcm2PalySameSelectPlay,pcmPlayer,&pcm2play::fromProtocolMessageSameSelectPlay);
    connect(this,&ProtocolMessage::toPcm2playForChangeVolume,pcmPlayer,&pcm2play::fromProtocolMessageForChangeVolume);




}


int ProtocolMessage::availableRead(int availableReadNum)//返回值 没有用  用于 调试 每一帧数据
{
    qDebug()<<"YOU MOTHER FUCK :"<<availableReadNum;
    while(availableReadNum)
    {
//        if(availableReadNum < 816)// socket 最大缓冲区8k 协议 中最大的一条消息是语音传输816，该长度导致一次满8k不是整数取出完，所以类 当缓冲区中的数据小于816的时候就不取，继续从socket接受，当缓冲区打鱼816的时候在取。
//        {
//            break;
//        }
//        else
//        {
                 qDebug()<<"Read Start1:";
            QByteArray rec = socket->read(4);
            qDebug()<<"Read Start2:";
            int big_Length = byteHexToInt(rec,0);

            QByteArray tmpM;
            qDebug()<<"READ_START_big_Length:"<<big_Length;
            qDebug()<<QString::fromLocal8Bit("取出去解码后:剩余:")<<availableReadNum;

            QByteArray m805 = socket->read(big_Length-4);
            qDebug()<<"Read Start3:";
            QByteArray T = rec+m805;//一次处理的包 // 接受的所有减去头4个字节

                msg_Analysis(T);

            availableReadNum-=big_Length;
//        }

    }
    return availableReadNum;
}


//接收
//当 可用达到8192字节的时候 就会在读取之前 自动清空 导致 read不到 出错
void ProtocolMessage::my_Receive()
{
    qDebug()<<"protocolmessage_my_Receive()";
    int all_Length = socket->bytesAvailable();//一次接受几个包 不确定
   // ui->textEdit_2->append(QString::fromLocal8Bit("可用字节：") + QString::number(all_Length));
   // ui->lineEdit_4->setText(QString::fromLocal8Bit("可用字节：")+QString::number(all_Length));
    qDebug()<<"READ_XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX:"<<all_Length;
    if(all_Length > 0)
    {
        bool line = socket->blockSignals(1);//阻塞接受
        all_Length = availableRead(all_Length);//接受数据
       // ui->textEdit_2->append(QString::fromLocal8Bit("Now Length:")+QString::number(all_Length));
        socket->blockSignals(0);
    }else
        ;
}


void ProtocolMessage::socket_Receive(QTcpSocket * socket)
{
    qDebug()<<QString::fromLocal8Bit("接受socket");
    this->socket = socket;
}

//解析
void ProtocolMessage::msg_Analysis(QByteArray &arec)
{
    qDebug()<<QString::fromLocal8Bit("解析：");
    int r_id = byteHexToInt(arec,sizeof(int)*2);//先解析第三个字段 确定消息类型//8
    qDebug()<<"msg_type"<<r_id;

    if(r_id == 801)
    {
        int serverDigestLength = byteHexToInt(arec,sizeof(int)*3);//第4个字段 服务器摘要长度
        QString serverDigest = arec.mid(sizeof(int)*4,32);
        int voiceRecordTextLength = byteHexToInt(arec,32);//第6个字段 语音记录仪明文长度
        QString voiceRecordText = arec.mid(36,128);

        qDebug()<<QString::fromLocal8Bit("解析801-语音记录仪返回的验证信息:")<<serverDigestLength<<serverDigest<<voiceRecordTextLength<<voiceRecordText;

        //在服务器上对比Skey是否正确 正确的话继续
        int ret = verifySkey(localSkeyMD5(),serverDigest);//验证本地的md5和记录仪经过skey后发回来的md5
        if(ret)
        {
            qDebug()<<QString::fromLocal8Bit("记录仪skey正确性验证通过");
        }
        system("pause");

        setCmd801C(voiceRecordText);
        qDebug()<<QString::fromLocal8Bit("发送记录仪验证MD5信号");
        emit toRealTimeForVerifyVoiceRecordMD5();
    }

    if(r_id == 802)//返回查询内容
    {
        //ui->textEdit_2->append(QString::fromLocal8Bit("解析802r："));
        int record_Num = byteHexToInt(arec,sizeof(int)*3);
       // ui->textEdit_2->append(QString::fromLocal8Bit("记录条数：")+QString::number(record_Num));
        qDebug()<<"recore_Mum:"<<record_Num;
        emit toDeviceControlNum(record_Num);
        for(int i =0;i<record_Num;i++)//
        {
            qDebug()<<QString::fromLocal8Bit("第") +QString::number(i+1) + QString::fromLocal8Bit("条");
            QByteArray record_StartTime = arec.mid(sizeof(int)*4 +21*i,17);

            QString year = record_StartTime.mid(0,4);
            QString month = record_StartTime.mid(4,2);
            QString date = record_StartTime.mid(6,2);
            QString hour = record_StartTime.mid(8,2);
            QString min = record_StartTime.mid(10,2);
            QString sec = record_StartTime.mid(12,2);
            QString msec = record_StartTime.mid(14,3);
            QString print_StartTime = year+QString::fromLocal8Bit("年")+month+QString::fromLocal8Bit("月")+date+QString::fromLocal8Bit("日")+hour+QString::fromLocal8Bit("时")+min+QString::fromLocal8Bit("分")+sec+QString::fromLocal8Bit("秒")+msec+QString::fromLocal8Bit("毫秒");
            qDebug()<<QString::fromLocal8Bit("时间：")<<year<<month<<date<<hour<<min<<sec<<msec;
            qDebug()<<QString::fromLocal8Bit("起始时间：")+print_StartTime;

            int record_Length = byteHexToInt(arec,sizeof(int)*4 + 17 + 21*i);
            int record_Hour = record_Length/3600;
            int record_Min = record_Length%3600/60;
            int record_Sec = record_Length%3600%60;
            QString print_Length = QString::number(record_Hour)+QString::fromLocal8Bit("时")+QString::number(record_Min) + QString::fromLocal8Bit("分")+ QString::number(record_Sec) + QString::fromLocal8Bit("秒");
            qDebug()<<QString::fromLocal8Bit("长度：")<<record_Hour<<record_Min<<record_Sec;
            qDebug()<<QString::fromLocal8Bit("本条记录长度：")<<print_Length;

            QString print_EndTime = year+QString::fromLocal8Bit("年")+month+QString::fromLocal8Bit("月")+date+QString::fromLocal8Bit("日")+QString::number(hour.toInt()+record_Hour)+QString::fromLocal8Bit("时")+QString::number(min.toInt() +record_Min)+QString::fromLocal8Bit("分")+QString::number(sec.toInt()+record_Sec) +QString::fromLocal8Bit("秒")+msec+QString::fromLocal8Bit("毫秒");

            emit toDeviceControl(print_StartTime,print_EndTime,print_Length,record_Num);

        }
        int CID_StringLength = byteHexToInt(arec,sizeof(int)*4 +record_Num*21);
        QByteArray CID_String = arec.mid(sizeof(int)*4 +record_Num*21+sizeof(int));//本部分可从math上优化代码提高性能 v2.0
        qDebug()<<QString::fromLocal8Bit("CID字符串长度：")+QString::number(CID_StringLength);
        qDebug()<<QString::fromLocal8Bit("CID字符串：")+CID_String;
       // ui->textEdit_2->append(QString::fromLocal8Bit("CID字符串长度：")+QString::number(CID_StringLength));
       // ui->textEdit_2->append(QString::fromLocal8Bit("CID字符串：")+CID_String);

    }else if(r_id == 803)//查询发送结束信号
    {
        //ui->textEdit_2->append(QString::fromLocal8Bit("收到查询结束信号"));
    }else if(r_id == 805)//通知发送语音请求是否成功信号 如果成功接下来发送语音数据
    {
        memset(pcm,0,DECODE_BUFF_SIZE);

       int check_Result = byteHexToInt(arec,sizeof(int)*3) ;
       check_VoiceLength = byteHexToInt(arec,sizeof(int)*4);//该消息中记录额长度备用 用语确认 806发送的消息的正确性 有点相当于常用的校验位
        qDebug()<<"check_Result"<<check_Result;
        qDebug()<<"check_VoiceLength"<<check_VoiceLength;
        {
            //计算解码后的大小用于控制 语音进度条
             decodeDataLength = getDecodePcmDataLength(check_VoiceLength);
        }
       if(check_Result)
       {
         //   获取语音成功，语音长度是check_VoiceLength.
           //decodeDataLength转化为时间长度，
           //pcm裸流每分钟读取17640byte
           qDebug()<<QString::fromLocal8Bit("语音长度:")<<decodeDataLength;
           int second = decodeDataLength/16000;
           emit toDeviceControlGetMusicFileLength(second);
           qDebug()<<QString::fromLocal8Bit("告知DeviceControl音频的长度!");
       }else
           ;//ui->textEdit_2->append(QString::fromLocal8Bit("查询语音消息失败"));
    }else if(r_id == 806)//下位机开始发送语音数据信号
    {
            int data_Length = byteHexToInt(arec,sizeof(int)*3);

            QByteArray data_Voice =  arec.mid(sizeof(int)*4);
//开始解码并播放

            DecodeAdpcm2Pcm(data_Voice);//没有使用多线程导致 在传输的时候卡顿

    }else if(r_id == 807)
    {
        //ui->textEdit_2->append(QString::fromLocal8Bit("传送结果："));
        int transfer_Type = byteHexToInt(arec,sizeof(int)*3);
        emit toPcm2PlayReceiveOver();
        qDebug()<<"transfer_Type"<<transfer_Type;
        if(transfer_Type)
            ;//ui->textEdit_2->append(QString::fromLocal8Bit("正常结束"));
        else
           ;// ui->textEdit_2->append(QString::fromLocal8Bit("异常结束"));
    }

}



void ProtocolMessage::setCmd800()
{
    QString str = "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefgh";
    M_800C.resize(144);
    M_800C =  this->intToByteHex(144)+intToByteHex(0)+intToByteHex(800)+intToByteHex(128)+str.toLatin1();
    qDebug()<<"M_800C"<<M_800C;
     qDebug()<<M_800C.size();
//What The Fuck  .toHex()直接转换成QString 不按位转换成byte   该方法用在在控件上显示16进制时转16进制
}


void ProtocolMessage::setCmd802C()
{
    M_802C.resize(58);
    QString startTime = "20170601010101000";
    QString endTime = "20180601010101000";
    M_802C = this->intToByteHex(58)+intToByteHex(0)+intToByteHex(802)+intToByteHex(1) +intToByteHex(17)+startTime.toLatin1()+intToByteHex(17)+endTime.toLatin1();
    qDebug()<<"802:"<<M_802C;
}

void ProtocolMessage::setCmd804C(int position)
{
    M_804C = intToByteHex(20)+intToByteHex(0)+intToByteHex(804)+intToByteHex(10)+intToByteHex(position);
    qDebug()<<"804Length:"<<strlen(M_804C);
    qDebug()<<"Msg:"<<M_804C;
}

void ProtocolMessage::setCmd808C()
{
    M_808C = intToByteHex(12)+intToByteHex(0)+intToByteHex(808);
    qDebug()<<"808Length:"<<strlen(M_808C);
    qDebug()<<"Msg:"<<M_808C;
}

void ProtocolMessage::setCmd809C()
{
    M_809C = intToByteHex(12)+intToByteHex(0)+intToByteHex(809);
    qDebug()<<"809Length:"<<strlen(M_809C);
    qDebug()<<"Msg:"<<M_809C;
}

QByteArray ProtocolMessage::intToByteHex(int number)//大端 网络字节序
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
 * int position: 是为解析消息方便引入的  解析个字段到strings  四个字节转一个int
*/
int ProtocolMessage::byteHexToInt(QByteArray arry, int postion)//big 大端 网络字节序
{
    int value;
    value = (int)((arry[postion+3] & 0xFF)
        | ((arry[postion + 2] << 8) & 0xFF00)
        | ((arry[postion + 1] << 16) & 0xFF0000)
        | ((arry[postion + 0] << 24) & 0xFF000000));
    return value;
}

void ProtocolMessage::setSocket(QTcpSocket * sock)
{
   // qDebug()<<"sock"<<sock;
    //qDebug()<<"socket"<<socket;
    this->socket = sock;
}

void ProtocolMessage::setDufaultVoiceDownDir()
{
    voiceDownRootDir = QDir::currentPath() + "/" +"voice";
}

void ProtocolMessage::fromDeviceControl(QString string)
{
    qDebug()<<"LAST**********************:"<<string;
    voiceDownRootDir = "";
    voiceDownRootDir = string+"/";
}

void ProtocolMessage::DecodeAdpcm2Pcm(QByteArray &data_Voice)//
{
    BYTE adpcm[FILE_BUFF_SIZE]; //adpcm buff
    memset(pcm, 0, DECODE_BUFF_SIZE);
    QByteArray rd;
    int decodeOneTimeCount = 0;
    localAvailableRead = localAvailableRead + data_Voice;
//    qDebug()<<QString::fromLocal8Bit("接受可用数据大小:")<<localAvailableRead.length();

    while(1)
    {
        int tmpLength =  localAvailableRead.length();
        if(tmpLength >= FILE_BUFF_SIZE)//如果现在的缓冲区中的数据>页大小 就 取出来一个页大小的数据去解码。
        {

            rd = localAvailableRead.mid(0,FILE_BUFF_SIZE);
            check_TempLength =check_TempLength + FILE_BUFF_SIZE;
            localAvailableRead = localAvailableRead.mid(FILE_BUFF_SIZE);
            //qDebug()<<"break"<<localAvailableRead.length();
        }else
        {
//            qDebug()<<"LLL:"<<(check_VoiceLength - check_TempLength);
//            qDebug()<<QString::fromLocal8Bit("localAvailableRead:")<<localAvailableRead.size();

            qDebug()<<"data_Voice.Length:"<<data_Voice.length();
            if(data_Voice.length() == 800)//如果语音总长度 - 已经读的 = 剩余没有读的 >一个页 那就跳出继续读
            {
                break;//该句会在最后
            }else
            {
                 rd = localAvailableRead.mid(0,FILE_BUFF_SIZE);//************************测试最后一个解码包
                 qDebug()<<QString::fromLocal8Bit("源文件最后取出大小:")<<rd.length();
            }
        }
//****************************************目前解码后最小********************************************
        BYTE *btmp =(BYTE*)rd.data();
    test_allDataLength = test_allDataLength + rd.length();
    qDebug()<<"test_allDataLength:"<<test_allDataLength;
        iTestCount +=1;
        qDebug()<<"BBBBB:"<<rd.length();
        int len = To->DecodeBuff(btmp,rd.length(),(short *)pcm);//rockwell官方解码器  pcm解完一页的长度
        test_allPCMDataLength = test_allPCMDataLength + len;
        qDebug()<<"test_allPCMDataLength:"<<test_allPCMDataLength;

        playBufferInfo = (char *)pcm;

//测试最后一个解码包*************************************
//        if(iTestCount ==28)
//        {
            QFile F("C:/Users/shenmingzh/Desktop/testDATA/QQQQQ.pcm");
            F.open(QIODevice::Append);
            int iCount = F.write((char *)btmp,rd.length());

            qDebug()<<QString::fromLocal8Bit("adpcm写入计数:")<<iCount;
            F.close();
//        }

        if(selectModel)
        {
            qDebug()<<"samesamesameWay"<<sameWay;
           if(sameWay)
           {

            }else
            {
               qDebug()<<" 55555555555555555555555555";
                emit toPcmToPlay(playBufferInfo,len);
            }
        }
        else
        {
            qDebug()<<QString::fromLocal8Bit("iTestCount:")<<iTestCount;

            //转码后 保存到文件
                    QFile F("C:/Users/shenmingzh/Desktop/testDATA/Decode.wav");
                    F.open(QIODevice::Append);
                    int iCount = F.write((char*)pcm,len);
                    qDebug()<<QString::fromLocal8Bit("pcm写入计数:")<<iCount;
                    F.close();
        }
        break;
    }

playBufferInfo = NULL;
}


void ProtocolMessage::fromDeviceControl_2(int position, bool way,bool selectSameOr)//position 是用户选择的第几条数据的索引值
{
    selectModel = way;
    if(selectModel)//play
    {
        if(selectSameOr)//如果两次选择 相同  直接从 固定缓冲区 拿数据播放 否则 记录仪发送语音数据
        {
            sameWay = true;
            emit toPcm2PalySameSelectPlay(true);
        }
        else
        {
            sameWay = false;
            setCmd804C(position);
            emit toPcm2PalySameSelectPlay(false);
        }
    }
    else//下载 操作直接请求记录仪
    {
        setCmd804C(position);
    }

qDebug()<<"----XXX------:"<<selectSameOr<<selectModel;
}



int ProtocolMessage::getDecodePcmDataLength(int adpcmDataLength)
{
    int tt = (adpcmDataLength*4 - adpcmDataLength*0.1752988);
    qDebug()<<QString::fromLocal8Bit("解码后大小:")<<tt;
    return tt;
}

void ProtocolMessage::fromDeviceForTopcm2play(bool type)
{
    emit toPcm2PlayOrPauseControl(type);
}

void ProtocolMessage::fromDeviceForTopcm2playClearAllBuffer(int volume)//ok
{

    emit toPcm2PlayForClearAllBuffer(volume);
    localAvailableRead.clear();
}

void ProtocolMessage::fromDeviceResetCount()
{
    test_allDataLength = 0;
    test_allPCMDataLength = 0;
    iTestCount = 0;
    localAvailableRead.clear();
}

void ProtocolMessage::fromDeviceForToPcm2PlayForStopDistancePlay()
{
    emit toPcm2PalyForStopDistancePlay();
}

void ProtocolMessage::fromPcm2PlayForTellSameSelectMusicLength(int len)
{
    int second = len/16000;
    emit toDeviceControlGetMusicFileLength(second);
}

void ProtocolMessage::fromPcm2PlayForTellMusicPlayOver()
{
    emit toDeviceTellMusicPlayOver();
}

void ProtocolMessage::fromDeviceControlForToPcm2playForChangeVolume(int volume)
{
    emit toPcm2playForChangeVolume(volume);
}

void ProtocolMessage::setCmd801C(QString voiceRecordText)
{
    QString nowTime = QDateTime::currentDateTime().toString("yyyymmddhhmmsszzz");
    qDebug()<<QString::fromLocal8Bit("当前时间:")<<nowTime;



    QString voiceRecordMD5Result32 = getMD5Result(voiceRecordText,rkey);
    QString voiceRecordMD5Result16 = voiceRecordMD5Result32.mid(8,16);//16位长
    M_801C = intToByteHex(53)+intToByteHex(0)+intToByteHex(801)+intToByteHex(17)+nowTime.toLatin1()+intToByteHex(16)+voiceRecordMD5Result16.toLatin1();
    qDebug()<<QString::fromLocal8Bit("M801C消息:")<<M_801C.toHex();
    qDebug()<<QString::fromLocal8Bit("M801C消息:")<<M_801C;
}

QString ProtocolMessage::getMD5Result(QString Text, uint4 key[])
{
    MD5 serverMD5(Text.toStdString(),key);
    return QString::fromStdString(serverMD5.md5());
}


bool ProtocolMessage::verifySkey(QString localMD5,QString skeyMD5)//localMD5:
{
    if(localMD5 == skeyMD5)
        return 1;

    return 0;
}


QString ProtocolMessage::localSkeyMD5()
{
    MD5 serverMD5(text.toStdString(),skey);
    QString localSkeyMD5_32 = QString::fromStdString(serverMD5.md5());
    qDebug()<<QString::fromLocal8Bit("本地MD5_32:")<<localSkeyMD5_32;
    QString localSkeyMD5_16 = localSkeyMD5_32.mid(8,16);//16位长
    qDebug()<<QString::fromLocal8Bit("本地MD5:")<<localSkeyMD5_16;
    return localSkeyMD5_16;
}

void ProtocolMessage::fromProtocolMessageForSetSocket(QTcpSocket * socket)
{
    //从realtimework发送给msg的 800命令
    this->socket = socket;



    //返回给realtimeFormsocket赋值完成,可以进行800信号传送
    emit toRealTimeFormForSocketOK();
}


