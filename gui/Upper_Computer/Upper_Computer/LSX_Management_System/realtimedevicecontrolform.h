#ifndef REALTIMEDEVICECONTROLFORM_H
#define REALTIMEDEVICECONTROLFORM_H

#include <QWidget>
#include <QTcpServer>
#include <qtcpsocket>
#include <QMediaPlayer>
#include <app/global.h>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <app/global.h>
#include <QComboBox>
#include "app/protocolmessage.h"
#include "app/imessagebox.h"
#include <QMouseEvent>

#define DISTENSE 1
#define LOCAL      0


//wav 信息头
struct WAVFILEHEADERINFO
{
    // RIFF 头;
    char RiffName[4];
    unsigned long nRiffLength;

    // 锟斤拷锟斤拷锟斤拷锟酵憋拷识锟斤拷;
    char WavName[4];

    // 锟斤拷式锟斤拷锟叫的匡拷头;
    char FmtName[4];
    unsigned long nFmtLength;

    // 锟斤拷式锟斤拷锟叫的匡拷锟斤拷锟斤拷;
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned long nSampleRate;
    unsigned long nBytesPerSecond;
    unsigned short nBytesPerSample;
    unsigned short nBitsPerSample;

    // 锟斤拷锟捷匡拷锟叫的匡拷头;
    char    DATANAME[4];
    unsigned long   nDataLength;
};


namespace Ui {
class RealTimeDeviceControlForm;
}

class RealTimeDeviceControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeDeviceControlForm(QWidget *parent = 0);
    ~RealTimeDeviceControlForm();
    void writeWavHeader(int second, QString fileName);
    void getVoiceDirFile(QString dirPath);
    void setThisUISocket();

signals:
    void toProtocolMessageForSetSocket(QTcpSocket * socket);//从realtimeForm 传送过来的socket用育my_Receive接收消息

public slots:
    void fromDevicePollingForm(QTcpSocket *socket, QString deviceInfo[8]);
    void fromDevicePollingFormForGotProtocolMessage(QTcpSocket * socket);


    void fromRealTimeFormForSocketOK();


    void deviceControlSelectDevice(QString sql,QString currentSelectData,QComboBox *comBox,int indexValue);

#define sw "select * from jian where duan=:ceshi"





//private:
public:
    Ui::RealTimeDeviceControlForm *ui;
    void setInitStyle();
    void updateTableViewShow();
    void setLocalVoiceValue();

    void readINIForRebootSetVolume();
    void writeINIForShutDownAppRecodVolume(int voiceVolume);
//    void rebootSetVolume();
//    void shutDownAppRecodVolume();

signals:
    void toProtocolMessage(QString);
    void toLoginDialogForCheckDB();

    void toMainWindow();

    void toProtocolMessage_2(int,bool,bool);

    void toProtocolMessageForPlayMusic(bool);
    void toProtocolMessageForToPcm2playClearPlayAllBUffer(int volume);
    void toProtocolMessageForResetCount();
    void toProtocolMessageForToPcm2PlayStopPlay();
    void toProtocolMessageForToPcm2playForChangeVolume(int);

public slots:
    void fromMainWindow(QString);
    void fromProtocolMessage(QString print_Time, QString print_EndTime, QString print_Length, int);
    void fromProtocolMessageNum(int);
    void fromProtocolMessageSentMusicFileLength(int second);
    void fromProtocolMessageTellMusicPlayOver();
    void fromMainWindowForSaveInfo();
    void fromProtocolMessageForVerifyVoiceRecordMD5();


private slots:

    void showDistansePlayTime();
    void on_pushButton_3_clicked();
   // void slot_newConnection();
   // void my_receive();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();
    void PLAYMUSIC();
    void DOWNLOADMUSIC();
//    void SelectStatus(const QItemSelection &selected, const QItemSelection &deselected);


//extern MysqlSupport mysql;

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);

    void on_comboBox_3_activated(const QString &arg1);

    void on_comboBox_4_activated(const QString &arg1);

    void on_comboBox_5_activated(const QString &arg1);
    void initComboBox();

    void on_verticalSlider_sliderMoved(int position);

    void on_pushButton_5_clicked();

    void showNowPosition();
    void setMusicTime(qint64 dx,qint64 px);

    void on_radioButton_clicked(bool checked);

    void on_pushButton_6_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);


    void on_pushButton_2_clicked();

    void getMusicFile(QString musicPath);
    void nowConnectStatus();

    void setInitStyleTableview();


    void on_tableView_pressed(const QModelIndex &index);


    void on_tableView_doubleClicked(const QModelIndex &index);


    void checkSockeConnectSttaus();
    void reConnectSocekt();




    void on_tableView_clicked(const QModelIndex &index);


    void on_tableView_2_doubleClicked(const QModelIndex &index);



    void on_addDuan_CloseButton_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
//    bool eventFilter(QObject *obj, QEvent *event);

private:
    QTcpServer *  server;
    QTcpSocket * socket;
    QMediaPlayer * voicePlayer;

    QString duan_Default_Data;
    QString jian_Default_Data;
    QString qu_Default_Data;
    QString station_Default_Data;
    QString device_Default_Data;

    global *deviceControl_global;

    QString localDirPath;
    QString voiceDirPath;

    QString voiceDownRootDir;

    QString duan;
    QString jian;
    QString qu;
    QString station;


    bool playAndPauseControl;
    qint64 musicLength;
    qint64  musicStopPosition;
    bool loopPlayModel;
    bool voiceStatus;
    qint64 voiceSlienceRecover;

    QStandardItemModel * voiceLocalDataModel;
    QString musicPath;


    ProtocolMessage * msg;//监控初始化的时候 初始化 msg

    bool changeVoiceRootDirFlag;
    bool connectStatus;
    QTimer *connectStatusTimer;

    QStandardItemModel *  tableviewModel;
    int record_AllNum;
    int record_PrintCount;
    bool pushButtonStatus;
    bool pushButtonDisconnectStatus;

    int tableview_SelectRow;

    int theMusicFileLength;//second

//    int connectStatus;
    QTimer *checkSocketStatusTimer;
    QTimer  *reconnectSocket;
    int reconnectCount;



private:
    bool playType;
    bool distensePlayOrPauseControl;
    QTimer distensePlayTime;

    int showDistansePlayTimeVariable;
    int PREVIndexRow;
    bool musicSelectStatus;
    QString doubleClickedMusicPath;
    QAction *playPCM;
    QAction *downloadWAV;
    QString connectIp;
    quint16 connectPort;
    bool selectMusicPlaying;
    bool distanceOneMusicPlayOver;

    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下

};

#endif // REALTIMEDEVICECONTROLFORM_H
