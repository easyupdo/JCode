#ifndef PROTOCOLMESSAGE_H
#define PROTOCOLMESSAGE_H

#include <QByteArray>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include <QObject>
#include <QDateTime>
#include "adpcm2pcm.h"
#include "pcm2play.h"
#include "app/md5.h"
#define PLAY true
#define PAUSE false
#define DOWNLOAD false
typedef unsigned int uint4;

class ProtocolMessage:public QObject
{
    Q_OBJECT
public:
    ProtocolMessage(QObject * parent = 0);

public:
    void setCmd800();
    void setCmd801C(QString voiceRecordText);
    void setCmd802C();
    void setCmd804C(int position);
    void setCmd808C();
    void setCmd809C();
    bool verifySkey(QString,QString);//验证本地skey生成的密钥和通过记录仪上skey生成的密钥 是否一样
    QString localSkeyMD5();//服务器本地skey生成密钥  返回生成的16位的密钥
    QByteArray intToByteHex(int number);
    int byteHexToInt(QByteArray arry, int postion);
    void msg_Analysis(QByteArray &arec);
    char ConvertHexChar(char ch);

    void setSocket(QTcpSocket *);

    void setDufaultVoiceDownDir();
    void DecodeAdpcm2Pcm(QByteArray &data_Voice);//
    int getDecodePcmDataLength(int);
    QString getMD5Result(QString Text, uint4 key[]);

signals:
    void toRealTimeFormForSocketOK();


public slots:
    void socket_Receive(QTcpSocket * socket);//带socket的接受方法
    void my_Receive();//巡查方式接受方法,如果socket是在子线程创建的 降socket传递过来
    void fromProtocolMessageForSetSocket(QTcpSocket *socket);


private slots:
    int availableRead(int availableRead);
    void fromDeviceControl(QString);


public slots:
    void fromDeviceControl_2(int position, bool way, bool selectSameOr);
    void fromDeviceForTopcm2play(bool type);
    void fromDeviceForTopcm2playClearAllBuffer(int volume);
    void fromDeviceResetCount();
    void fromDeviceForToPcm2PlayForStopDistancePlay();
    void fromPcm2PlayForTellSameSelectMusicLength(int len);
    void fromPcm2PlayForTellMusicPlayOver();
    void fromDeviceControlForToPcm2playForChangeVolume(int volume);
signals:
    void toDeviceControl(QString,QString,QString,int);
    void toDeviceControlNum(int);
    void toPcmToPlay(char *,int);
    void toDeviceControlGetMusicFileLength(int);
    void toPcm2PlayOrPauseControl(bool type);
    void toPcm2PlayForClearAllBuffer(int);
    void toPcm2PlayReceiveOver();
    void toPcm2PalySameSelectPlay(bool);
    void toPcm2PalyForStopDistancePlay();
    void toDeviceTellMusicPlayOver();
    void toPcm2playForChangeVolume(int);

    void toRealTimeForVerifyVoiceRecordMD5();


public:
    QByteArray M_800C;          //800 md5认证 0:Command    1:Result     M_XXXC: M代表message XXX代表消息ID C代表消息是由服务器到记录仪（R代表消息由记录仪到服务器）
    QByteArray M_801C;
    QByteArray M_802C;
    QByteArray M_804C;
    QByteArray M_808C;
    QByteArray M_809C;

    QTcpSocket * socket;

    int voice_Length;

    QFile *rF;

    int one;

    QByteArray voice_Buff;

    QString voiceDownRootDir;

    //解码并播放
    adpcm2Pcm * To;
    QByteArray localAvailableRead;
    char *playBufferInfo;
     QTimer * timer;
     BYTE pcm[DECODE_BUFF_SIZE];//decode 2 pcm buff

     bool selectModel;

     int iTestCount;

     int check_VoiceLength;
     int check_TempLength;

     int test_allDataLength;
     int test_allPCMDataLength;
     int decodeDataLength;

     int PREVIndexRow;
     bool sameWay;


     uint4 skey[4];
     uint4 rkey[4];
     QString text;



};

#endif // PROTOCOLMESSAGE_H
