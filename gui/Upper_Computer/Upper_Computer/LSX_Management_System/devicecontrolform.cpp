#include "devicecontrolform.h"
#include "ui_devicecontrolform.h"
#include <QFile>
#include "app/mysqlsupport.h"
#include "app/global.h"
#include <QFileInfoList>
#include <QFileInfo>
#include <QDir>
#include <QStandardItemModel>
#include <QTimer>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QSettings>


DeviceControlForm::DeviceControlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceControlForm)
{
    ui->setupUi(this);
    changeVoiceRootDirFlag = false;
    connectStatus = false;
    pushButtonStatus = false;
    tableview_SelectRow = 0;
    PREVIndexRow = -1;
    distensePlayOrPauseControl = false;
    musicSelectStatus =false;
    showDistansePlayTimeVariable = 0;
    selectMusicPlaying = false;
    distanceOneMusicPlayOver = false;
    connect(&distensePlayTime,&QTimer::timeout,this,&DeviceControlForm::showDistansePlayTime);



    deviceControl_global= new global;
//    deviceControl_global->
    connect(this,&DeviceControlForm::toLoginDialogForCheckDB,deviceControl_global,&global::fromUserSqlClassForCheckDB);
    //初始化proto_Message
    socket = new QTcpSocket;

    msg = new ProtocolMessage;
    connect(this,&DeviceControlForm::toProtocolMessage_2,msg,&ProtocolMessage::fromDeviceControl_2);
    connect(socket,SIGNAL(readyRead()),msg,SLOT(my_Receive()));//协议中接受

    connect(this,SIGNAL(toProtocolMessage(QString)),msg,SLOT(fromDeviceControl(QString)));
    connect(msg,&ProtocolMessage::toDeviceControl,this,&DeviceControlForm::fromProtocolMessage);
    connect(msg,&ProtocolMessage::toDeviceControlNum,this,&DeviceControlForm::fromProtocolMessageNum);
    connect(msg,&ProtocolMessage::toDeviceControlGetMusicFileLength,this,&DeviceControlForm::fromProtocolMessageSentMusicFileLength);
    connect(msg,&ProtocolMessage::toDeviceTellMusicPlayOver,this,&DeviceControlForm::fromProtocolMessageTellMusicPlayOver);

    connect(this,&DeviceControlForm::toProtocolMessageForPlayMusic,msg,&ProtocolMessage::fromDeviceForTopcm2play);
    connect(this,&DeviceControlForm::toProtocolMessageForToPcm2playClearPlayAllBUffer,msg,&ProtocolMessage::fromDeviceForTopcm2playClearAllBuffer);
    connect(this,&DeviceControlForm::toProtocolMessageForToPcm2PlayStopPlay,msg,&ProtocolMessage::fromDeviceForToPcm2PlayForStopDistancePlay);
   connect(this,&DeviceControlForm::toProtocolMessageForResetCount,msg,&ProtocolMessage::fromDeviceResetCount);
   connect(this,&DeviceControlForm::toProtocolMessageForToPcm2playForChangeVolume,msg,&ProtocolMessage::fromDeviceControlForToPcm2playForChangeVolume);


    // qDebug()<<"*******************:"<<socket;
    msg->setSocket(socket);
    QString rootVoicePath = QDir::currentPath();//获取当前的目录**************
    rootVoicePath = "C:/Users/shenmingzh/Desktop";//语音文件根目录*******
    voiceDirPath = rootVoicePath + "/" + "voice";
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView->horizontalHeader()->setSectionsClickable(false);
    ui->tableView_2->horizontalHeader()->setSectionsClickable(false);
    setInitStyle();
    tableviewModel = new QStandardItemModel;
    ui->tableView->setModel(tableviewModel);
    setInitStyleTableview();




    loopPlayModel = false;
    voiceStatus = false;
    voiceSlienceRecover = 0;
    record_AllNum = 0;
    record_PrintCount = 0;






    //音频播放
    voicePlayer = new QMediaPlayer(this);
//    voicePlayer->setVolume(30);
    ui->pushButton_6->setIcon(QIcon(":/image/speaker.png"));
    ui->pushButton_6->setStyleSheet("background-color: rgb(240 ,240, 240);");///小喇叭的背景颜色
    setLocalVoiceValue();

//    QString musicName = "C:/Users/shenmingzh/Desktop/testDATA/TTTT.wav";
//    qDebug()<<"TTTTTTTTTTTTTTTTTTTTTTT"<<musicName;

    playAndPauseControl = false;


    //音频进度条位置显示定时器
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(showNowPosition()));
    timer->start(1000);

    deviceControlSelectDevice(deviceControl_global->sql_SelectDuan,"first",ui->comboBox,0);
   // initComboBox();

    //server = new QTcpServer;
    //bool status = server->listen(QHostAddress::LocalHost,8888);

    //this->show();


//tableview添加右键菜单
    playPCM = new QAction(this);
    downloadWAV = new QAction(this);
    playPCM->setText(QString::fromLocal8Bit("播放"));
    downloadWAV->setText(QString::fromLocal8Bit("下载"));
    playPCM->setEnabled(false);
    downloadWAV->setEnabled(false);
    ui->tableView->addAction(playPCM);
    ui->tableView->addAction(downloadWAV);
    connect(playPCM, SIGNAL(triggered()), this, SLOT(PLAYMUSIC()));
    connect(downloadWAV, SIGNAL(triggered()), this, SLOT(DOWNLOADMUSIC()));

    //
//    QItemSelectionModel * md = ui->tableView->selectionMode();
//    connect(md,&QItemSelectionModel::selectionChanged,this,&DeviceControlForm::SelectStatus);
    //tableview_2添加右键菜单
    QAction * playLocalPCM = new QAction(this);
    playLocalPCM->setText(QString::fromLocal8Bit("播放"));
    playLocalPCM->setIcon(QIcon(":/image/play.ico"));
    ui->tableView_2->addAction(playLocalPCM);
//    playLocalPCM->setSeparator(true);
//    playLocalPCM->set


    readINIForRebootSetVolume();//读取上次音量
}

DeviceControlForm::~DeviceControlForm()
{
    delete ui;
}

/*
void DeviceControlForm:: slot_newConnection()
{
    QFile *file = new QFile("C:/Users/shenmingzh/Desktop/testDATA/test.adpcm");
    file->open(QIODevice::ReadOnly);
    socket = new QTcpSocket;
    socket = server->nextPendingConnection();
    QHostAddress * hostAddress = new QHostAddress();
    QHostAddress hAddress = socket->peerAddress();
    qDebug()<<"hAddress:"<< hAddress.toString();
    QString recBuff = socket->readAll();
    qDebug()<<"recBuff:"<<recBuff;
    connect(socket, SIGNAL(readyRead()), this, SLOT(my_receive()));

}
*/

void DeviceControlForm::writeWavHeader(int second,QString fileName)
{ // 开始准备WAV的文件头
    WAVFILEHEADER WavFileHeader;
    qstrcpy(WavFileHeader.RiffName, "RIFF");
    qstrcpy(WavFileHeader.WavName, "WAVE");
    qstrcpy(WavFileHeader.FmtName, "fmt ");

    WavFileHeader.nFmtLength = 16;  //  表示 FMT 的长度
    WavFileHeader.nAudioFormat = 1; //这个表示 PCM 编码;

    qstrcpy(WavFileHeader.DATANAME, "data");

    WavFileHeader.nBitsPerSample = 16;
    WavFileHeader.nBytesPerSample = 2;
    WavFileHeader.nSampleRate = 8000;
    WavFileHeader.nBytesPerSecond = 16000;
    WavFileHeader.nChannleNumber = 1;

    int voiceDataSecond = 50;//要求下位机在消息中包含音频文件的播放长度 单位second   在上位机要使用该事件来计算音频数据的总长度  16000*second
    int wavHeadSize = sizeof(WavFileHeader);
    qint64 voiceDataLen = WavFileHeader.nBytesPerSecond *voiceDataSecond;

    WavFileHeader.nRiffLength = voiceDataLen - 8 + wavHeadSize;
    WavFileHeader.nDataLength = voiceDataLen;
//本地保存根目录从系统设置的语音下载目录获取
    QFile F("C:/Users/shenmingzh/Desktop/testDATA/Decode.wav");//写wav头
    F.open(QIODevice::WriteOnly);
    F.write((char *)&WavFileHeader, wavHeadSize);
    F.close();
}

//void DeviceControlForm::my_receive()
//{

//    QByteArray ra = socket->read(socket->bytesAvailable());
//    QString str(ra);
//    qDebug()<<str;
//    QFile F("C:/Users/shenmingzh/Desktop/testDATA/TTTT.wav");
//    F.open(QIODevice::Append);
//    F.write(ra);
//    F.close();

//}
void DeviceControlForm::on_pushButton_3_clicked()//download
{
    socket->write(this->msg->M_804C);
}
//********BUG******本地语音目录获取问题 已经修正20170804

void DeviceControlForm::on_pushButton_clicked()//connect
{
    connectStatus = !connectStatus;
    QSqlQuery query;
    QString sql = QString::fromLocal8Bit("select ip,port from device where duan = '%1' and jian = '%2' and qu = '%3' and station = '%4' and deviceid = '%5'")
            .arg(ui->comboBox->currentText(),ui->comboBox_2->currentText(),ui->comboBox_3->currentText(),ui->comboBox_4->currentText(),ui->comboBox_5->currentText());
    qDebug()<<"SQL"<<sql;
    query.prepare(sql);

    query.exec();
    if(query.next())
    {
        connectIp = query.value(0).toString();
        connectPort = query.value(1).toInt();
    }
    qDebug()<<"connectIp:"<<connectIp<<"connectPort:"<<connectPort;

    if(connectStatus)//可以连接
    {
        //socket = server->nextPendingConnection();
        socket->connectToHost(QHostAddress(connectIp),connectPort);//连接目标设备
        ui->pushButton->setText(QString::fromLocal8Bit("正在连接"));
        ui->pushButton->setStyleSheet("background-color: #b4d3e8");
        ui->pushButton->setEnabled(false);
        pushButtonDisconnectStatus = true;
        connectStatusTimer = new QTimer;
        connect(connectStatusTimer,SIGNAL(timeout()),this,SLOT(nowConnectStatus()));
        connectStatusTimer->start(1000);
    }else//断开连接
    {
        updateTableViewShow();
        pushButtonDisconnectStatus = false;
        ui->pushButton->setText(QString::fromLocal8Bit("连接"));
        socket->disconnectFromHost();
        qDebug()<<QString::fromLocal8Bit("断开当前连接!");
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->comboBox_5->setEnabled(true);
    }



}
//检查网络连接状态
void DeviceControlForm::checkSockeConnectSttaus()
{
    qDebug()<<QString::fromLocal8Bit("socket状态:")<<socket->state();
    if(socket->state() == QAbstractSocket::UnconnectedState)
    {
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("设备连接已经断开!"),"prompt");
        box.exec();
        updateTableViewShow();//掉线更新显示
//        ui->label_20->setText(QString::fromLocal8Bit("离线播放"));
//        musicSelectStatus =false;//掉线就得重新选择播放
        {
            //TODO 设置掉线故障记录
            ui->label_18->clear();
            ui->label_20->setText(QString::fromLocal8Bit("本地播放"));
            playPCM->setEnabled(false);
            downloadWAV->setEnabled(false);
        }

        checkSocketStatusTimer->stop();
        delete checkSocketStatusTimer;
        {
            connectStatus = false;
            pushButtonDisconnectStatus = false;
            ui->pushButton->setText(QString::fromLocal8Bit("连接"));
            ui->comboBox->setEnabled(true);
            ui->comboBox_2->setEnabled(true);
            ui->comboBox_3->setEnabled(true);
            ui->comboBox_4->setEnabled(true);
            ui->comboBox_5->setEnabled(true);
        }
    }
        else if(socket->state() == QAbstractSocket::ConnectingState)
        {
            qDebug()<<QString::fromLocal8Bit("正在连接... ...");
        }//else if(socket->state() == QAbstractSocket::ConnectedState)

//        on_pushButton_clicked();

}

void DeviceControlForm::nowConnectStatus()
{
    if(socket->state() == QAbstractSocket::ConnectedState)//如果已经连接到 则开始发送心跳包 保活
    {
        qDebug()<<"socekt status:"<<socket->state();
        ui->pushButton->setText(QString::fromLocal8Bit("断开连接"));
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->comboBox_4->setEnabled(false);
        ui->comboBox_5->setEnabled(false);
        ui->pushButton->setEnabled(true);
        ui->pushButton->setStyleSheet("background-color: #2297dd");
        ui->label->setText(ui->comboBox_5->currentText());
        connectStatusTimer->stop();
        delete connectStatusTimer;
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("设备已连接"),"prompt");
        int status = box.exec();
        checkSocketStatusTimer = new QTimer;
        connect(checkSocketStatusTimer,SIGNAL(timeout()),this,SLOT(checkSockeConnectSttaus()));//1s一次检测网络是否断开
        checkSocketStatusTimer->start(1000);
    }else if(socket->state() == QAbstractSocket::ConnectingState)
    {
            qDebug()<<QString::fromLocal8Bit("正在连接");
            connectStatusTimer->stop();
            delete connectStatusTimer;
            reconnectSocket = new QTimer;
            connect(reconnectSocket,SIGNAL(timeout()),this,SLOT(reConnectSocekt()));
            reconnectSocket->start(1000);
            reconnectCount = 0;
//            checkSockeConnectSttaus();
    }else if(pushButtonStatus )
    {
//        ui->pushButton->setText(QString::fromLocal8Bit("连接"));
//        ui->pushButton->setEnabled(true);
//        connectStatus = false;
//        ui->pushButton->setStyleSheet("background-color: #2297dd");
//        ui->pushButton->setStyleSheet(".QPushButton:hover{ background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #5CACEE, stop:1 #4F94CD);}");
//        ui->pushButton->setStyleSheet(".QPushButton:pressed{ background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #5F94B4, stop:1 #70A9CC);}");
//        QMessageBox box;
//        if(pushButtonDisconnectStatus)
//        {
//            box.setText(QString::fromLocal8Bit("连接失败，请检查设备连接情况！"));
//        }else
//            box.setText(QString::fromLocal8Bit("连接已经断开"));
//        box.exec();
////        qDebug()<<QString::fromLocal8Bit("连接失败");
//        connectStatusTimer->stop();
//        delete connectStatusTimer;
    }

}

void DeviceControlForm::reConnectSocekt()//重连记录仪
{
    qDebug()<<"reconnectCount:"<<reconnectCount;
    reconnectCount += 1;
    if(reconnectCount != 5)//重连次数 也是重连时间 定时器是1s一次
    {
        if(socket->state() == QAbstractSocket::UnconnectedState)
        {
             socket->connectToHost(QHostAddress(connectIp),connectPort);
        }
        if(socket->state() == QAbstractSocket::ConnectedState)//在规定时间内连接上，终止定时器
        {
            reconnectSocket->stop();
            delete reconnectSocket;
            iMessageBox box;
            box.setUserMessage(QString::fromLocal8Bit("设备已连接"),"prompt");
            box.exec();
        }
    }else//超时连接 终止定时器
    {
        reconnectSocket->stop();
        delete reconnectSocket;
        ui->pushButton->setEnabled(true);
        connectStatus = false;
        ui->pushButton->setStyleSheet("background-color: #2297dd");
        ui->pushButton->setText(QString::fromLocal8Bit("连接"));
        iMessageBox box;
        box.setUserMessage(QString::fromLocal8Bit("设备连接超时!请检查设备连接情况"),"prompt");
        box.exec();
    }

}


void DeviceControlForm::on_pushButton_4_clicked()//voicePalyer
{
//  setLocalVoiceValue();
    qDebug()<<"XXXXXXXXXXXXX#####:"<<playAndPauseControl;
    if(musicSelectStatus)
    {
        this->playAndPauseControl = ! playAndPauseControl;
        if(this->playAndPauseControl)//暂停
        {
            if(playType)//远程
            {
//                ui->pushButton_4->setText(QString::fromLocal8Bit("暂停"));
                //远程 发送给
                ui->pushButton_4->setText(QString::fromLocal8Bit("播放"));
                distensePlayTime.stop();
                emit toProtocolMessageForPlayMusic(PAUSE);//*************************20170914：*需要调整pcm2play的播放的缓存区，考虑到循环播放,可以添加一个固定的缓存区。1.暂停播放位置好控制，2.循环好控制，不用每次发送信号播放，本地循环 //一定修正20170919
                qDebug()<<QString::fromLocal8Bit("发暂停信号");
//                distanceOneMusicPlayOver = false;
            }else
            {
                distensePlayTime.stop();
                emit toProtocolMessageForToPcm2PlayStopPlay();
                voicePlayer->play();
                 ui->pushButton_4->setText(QString::fromLocal8Bit("暂停"));
            }
        }
        else
        {
            if(playType)
            {
                qDebug()<<"distanceOneMusicPlayOver:"<<distanceOneMusicPlayOver;
                if(distanceOneMusicPlayOver)
                {
                    qDebug()<<QString::fromLocal8Bit("远程重播远程重播!");
                       this->PLAYMUSIC();
                    distanceOneMusicPlayOver = false;
                }else
                {
                //远程发送给
                ui->pushButton_4->setText(QString::fromLocal8Bit("暂停"));
                distensePlayTime.start();
                qDebug()<<QString::fromLocal8Bit("发播放信号");
                emit toProtocolMessageForPlayMusic(PLAY);
                }
            }else
            {
                //*------------------------------------重播/循环播放
                 ui->pushButton_4->setText(QString::fromLocal8Bit("播放"));
                qDebug()<<"musicStopPosition"<<musicStopPosition;
                voicePlayer->pause();
                this->voicePlayer->setPosition(musicStopPosition);
            }
        }
    }else
    {
        iMessageBox box;
        box.setMessageType("prompt");
        box.setMessageText(QString::fromLocal8Bit("请双击要播放的文件进行播放!"));
        box.exec();
    }
}

//*******************************后期整合修改 文件系统中语音文件命名规则*************************************
//获取语音文件夹下所有的文件  可以根据文件类型过滤
void DeviceControlForm::getVoiceDirFile(QString dirPath)//
{
    QSqlQueryModel *sqlModel = new QSqlQueryModel();
    voiceLocalDataModel = new QStandardItemModel();
     ui->tableView_2->setModel(voiceLocalDataModel);

    voiceLocalDataModel->setColumnCount(5);

    //ui->tableView_2->setModel(voiceLocalDataModel);
   //本地语音搜索文件系统
    qDebug()<<"dirPath:"<<dirPath;
    QDir voiceDir = QDir(dirPath);
    QFileInfoList fileInfoList = voiceDir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    int dirTX = fileInfoList.size();
    qDebug()<<"hang : "<<dirTX;
    QFileInfo fileInfo;
    for(int i = 0;i < dirTX ; i++)
    {
        fileInfo = fileInfoList.at(i);
        voiceLocalDataModel->setItem(i,0,new QStandardItem("2017070813:38"));
        voiceLocalDataModel->setItem(i,3,new QStandardItem(fileInfo.fileName()));

        QString TTT = "123456";
        //sqlModel->setQuery(QString("INSERT INTO music(NAME,singer,path)VALUES(TTT,'ZZ','DD');"));
        //QString recoreLength = "文件名";

        //语音记录搜索数据库
 /*       QSqlQuery query;//变量 插入数据库
          query.prepare("INSERT INTO music(NAME,singer,path)VALUES(:name,:singer,:path);");
          //.prepare("select *from music");
          query.bindValue(":name",fileInfo.fileName());
          query.bindValue (":singer","ipAddress");
          query.bindValue (":path","FFF");
          bool at =query.exec();
          sqlModel->setQuery("select * from music");//model 模式来查询
          ui->tableView_2->setModel(sqlModel);
          qDebug()<<at;
    */
    }
    // 设置headerData
    voiceLocalDataModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("起始时间"));
    voiceLocalDataModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("结束时间"));
    voiceLocalDataModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("录音长度"));
    voiceLocalDataModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("文件名"));
    voiceLocalDataModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备号"));


    voiceLocalDataModel->insertColumn(5);
     voiceLocalDataModel->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit(" "));
    // ui->tableView_2-
    // ui-
     //voiceLocalDataModel->
}




void DeviceControlForm::deviceControlSelectDevice(QString sql,QString currentSelectData,QComboBox *comBox,int indexValue)
{

    QStringList stringList1 ;
    QSqlQuery query;
    int qT = query.prepare(sql);
    if(currentSelectData!="first")
    {
        query.bindValue(":user_select",currentSelectData);
        qDebug()<<"------------------------------"<<query.lastQuery();
        //localDirPath = localDirPath+currentSelectData+"/";
    }else
        ;


//        qDebug()<<"DBTest:"<<query.isActive();

    if(!query.exec())
//    {
        emit toLoginDialogForCheckDB();
        emit toMainWindow();//发送给MainWindow 然后MainWindow发送信号给mysqlsupport检查数据库连接情况
//    }
    while(query.next())
    {
        qDebug()<<"DEVICE:"<<query.value(indexValue).toString();
        stringList1.append(query.value(indexValue).toString());
    }
    comBox->addItems(stringList1);
    if(ui->comboBox_5->currentText().size() > 0)//设备库中有设备可连接
    {
        pushButtonStatus = true;
        ui->pushButton->setEnabled(true);
        ui->pushButton->setStyleSheet("background-color: #2297dd");
        ui->pushButton->setStyleSheet(".QPushButton:hover{ background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #5CACEE, stop:1 #4F94CD);}");
        ui->pushButton->setStyleSheet(".QPushButton:pressed{ background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #5F94B4, stop:1 #70A9CC);}");
    }else
    {
        pushButtonStatus = false;

        ui->pushButton->setEnabled(false);
        ui->pushButton->setStyleSheet("background-color: #b4d3e8");
    }
        qDebug()<<"currentTextPPP；"<<ui->comboBox_5->currentText();

//        qDebug()<<""<<ui->comboBox_5->currentText().size();


    //获取本地语音记录
    QString path = voiceDirPath + "/"+ui->comboBox->currentText()+"/"+ui->comboBox_2->currentText()+"/"+ui->comboBox_3->currentText()+"/"+ui->comboBox_4->currentText()+"/"+ui->comboBox_5->currentText();
    musicPath = path;
    getMusicFile(musicPath);



}

void DeviceControlForm::getMusicFile(QString musicPath)
{
     getVoiceDirFile(musicPath);
    qDebug()<<"voice_path:"<<musicPath;
    voicePlayer->stop();
//    voicePlayer->setMedia(1);
    voicePlayer->setMedia(QUrl::fromLocalFile(""));
    if(!changeVoiceRootDirFlag)
    {
        voiceDownRootDir = musicPath;
        emit this->toProtocolMessage(voiceDownRootDir);
    }
}



//1 duan >> jian
void DeviceControlForm::on_comboBox_activated(const QString &arg1)
{
    musicSelectStatus = false;
//    updateTableViewShow();

    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();
    qDebug()<<"arg1"<<arg1;
    localDirPath = "/";
    duan = jian = qu = station = "";
    duan = arg1;
    localDirPath = localDirPath+arg1+"/";
    qDebug()<<"localDirPath!!!!"<<localDirPath;
    deviceControlSelectDevice(deviceControl_global->sql_SelectJian,ui->comboBox->currentText(),ui->comboBox_2,1);
    deviceControlSelectDevice(deviceControl_global->sql_SelectQu,ui->comboBox_2->currentText(),ui->comboBox_3,2);
    deviceControlSelectDevice(deviceControl_global->sql_SelectStation,ui->comboBox_3->currentText(),ui->comboBox_4,3);
    deviceControlSelectDevice(deviceControl_global->sql_SelectDevice,ui->comboBox_4->currentText(),ui->comboBox_5,4);
     //UPDATDE
}

//2 jian >> qu
void DeviceControlForm::on_comboBox_2_activated(const QString &arg1)
{
//    updateTableViewShow();
    musicSelectStatus = false;
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();
        int index = duan.length();
        qDebug()<<"index"<<index;
        localDirPath = localDirPath.left(index+2);
        localDirPath = localDirPath+arg1+"/";
        jian = arg1;
        qDebug()<<"localDirPath"<<localDirPath;
    deviceControlSelectDevice(deviceControl_global->sql_SelectQu,ui->comboBox_2->currentText(),ui->comboBox_3,2);
    deviceControlSelectDevice(deviceControl_global->sql_SelectStation,ui->comboBox_3->currentText(),ui->comboBox_4,3);
    deviceControlSelectDevice(deviceControl_global->sql_SelectDevice,ui->comboBox_4->currentText(),ui->comboBox_5,4);

}
//3 qu >> sation
void DeviceControlForm::on_comboBox_3_activated(const QString &arg1)
{
//    updateTableViewShow();
    musicSelectStatus = false;
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();
        {
            int index = duan.length()+jian.length();
            qDebug()<<"3index"<<index;
            localDirPath = localDirPath.left(index+3);
            localDirPath = localDirPath+arg1+"/";
            qu = arg1;
            qDebug()<<"localDirPath"<<localDirPath;
        }
    deviceControlSelectDevice(deviceControl_global->sql_SelectStation,ui->comboBox_3->currentText(),ui->comboBox_4,3);
    deviceControlSelectDevice(deviceControl_global->sql_SelectDevice,ui->comboBox_4->currentText(),ui->comboBox_5,4);
}
// station >> device
void DeviceControlForm::on_comboBox_4_activated(const QString &arg1)
{
//    updateTableViewShow();
    musicSelectStatus = false;
    ui->comboBox_5->clear();
    {
        int index = duan.length()+jian.length()+qu.length();
        qDebug()<<"index"<<index;
        localDirPath = localDirPath.left(index+4);
        localDirPath = localDirPath+arg1+"/";
        station = arg1;
        qDebug()<<"localDirPath"<<localDirPath;
    }
    deviceControlSelectDevice(deviceControl_global->sql_SelectDevice,ui->comboBox_4->currentText(),ui->comboBox_5,4);

}

void DeviceControlForm::on_comboBox_5_activated(const QString &arg1)
{
//    updateTableViewShow();
    musicSelectStatus = false;
    {
        int index = duan.length()+jian.length()+qu.length()+station.length();
        qDebug()<<"index"<<index;
        localDirPath = localDirPath.left(index+5);
        localDirPath = voiceDirPath +  "/"+ui->comboBox->currentText()+"/"+ui->comboBox_2->currentText()+"/"+ui->comboBox_3->currentText()+"/"+ui->comboBox_4->currentText()+"/"+ui->comboBox_5->currentText();;
        qDebug()<<"localDirPath"<<localDirPath;
    }

    getMusicFile(localDirPath);
    ui->label->setText(ui->comboBox_5->currentText());
}


void DeviceControlForm::initComboBox()
{
    QSqlQuery query;
    query.prepare(QObject::tr("select duan  from duan"));
    query.exec();
    QStringList stringList;
    while(query.next())
    {
        stringList<<query.value(0).toString();
    }
    ui->comboBox->addItems(stringList);
}


void DeviceControlForm::setInitStyle()
{
    QSqlQueryModel * model = new QSqlQueryModel;
    QString sql =  QObject::tr("select duan,jian,qu,station,deviceid from device where duan = '%1'").arg("");
    model->setQuery(sql);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("起始时间"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("结束时间"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("录音长度"));
    model->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("文件名"));
    model->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("设备号"));

    model->insertColumn(5);
     model->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit(" "));

//    ui->tableView->setModel(model);
    ui->tableView_2->setModel(model);
}

void DeviceControlForm::setInitStyleTableview()
{
    tableviewModel ->insertColumns(0,5);
    tableviewModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("起始时间"));
    tableviewModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("结束时间"));
    tableviewModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("录音长度"));
//    tableviewModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("文件名"));
    tableviewModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("设备号"));
    tableviewModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit(" "));


}



void DeviceControlForm::on_verticalSlider_sliderMoved(int position)//Min0 - Max100
{
    //TODO send a signal for distance play music set valume
    if(playType)//远程
        emit toProtocolMessageForToPcm2playForChangeVolume(position);
    else
    {
        qDebug()<<QString::fromLocal8Bit("当前音量XX:")<<position;
        voicePlayer->setVolume(position);

    }
}

void DeviceControlForm::on_pushButton_5_clicked()
{
  voicePlayer->stop();
  voicePlayer->setPosition(0);
  ui->pushButton_4->setText(QString::fromLocal8Bit("播放"));
  playAndPauseControl = false;
}


void DeviceControlForm::showNowPosition()//实时显示位置
{
    if(playType)//远程
    {
    }
    else
    {
        qint64 px = voicePlayer->position();//获取音频当前位置
        musicStopPosition = px;
      //  qDebug()<<"now"<<px;
        qint64 dx = voicePlayer->duration();//获取音频总长度
      //  qDebug()<<"dddd"<<dx;
        ui->horizontalSlider->setMaximum(dx);
        ui->horizontalSlider->setMinimum(0);
        ui->horizontalSlider->setSliderPosition(px);
        setMusicTime(dx,px);
        if(px == dx )//播放完
        {
            selectMusicPlaying = false;
            playAndPauseControl = false;
            voicePlayer->setPosition(0);
            if(loopPlayModel)
            {
                on_pushButton_4_clicked();
                ui->pushButton_4->setText(QString::fromLocal8Bit("暂停"));
                playAndPauseControl = true;
            }else
            {
                ui->pushButton_4->setText(QString::fromLocal8Bit("播放"));

            }
        }
    }


}


void DeviceControlForm::setMusicTime(qint64 dx,qint64 px)//讲音频文件长度转化为时分秒制
{
    qint64 time=dx;
    double secondDouble=time/1000;
    int minint=secondDouble/60;
    int secondint=secondDouble-minint*60;
    double secondtime1=px/1000;
    int minint1=secondtime1/60;
    int secondint1=secondtime1-minint1*60;
    QString t=QString("%0:%1").arg(QString::number(minint1),QString::number(secondint1));
    QString s=QString("%0:%1").arg(QString::number(minint),QString::number(secondint));
    //实时进度
    ui->label_3->setText(t);
    ui->label_11->setText(s);

}



void DeviceControlForm::on_radioButton_clicked(bool checked)//循环
{
      loopPlayModel = !loopPlayModel;
}



void DeviceControlForm::on_pushButton_6_clicked()
{
    voiceStatus = !voiceStatus;
    if(voiceStatus)
    {
        ui->pushButton_6->setIcon(QIcon("C:/Users/shenmingzh/Desktop/testDATA/speaker_mute.png"));
        voiceSlienceRecover = voicePlayer->volume();
        qDebug()<<voiceSlienceRecover;
        voicePlayer->setVolume(0);
        ui->verticalSlider->setValue(0);
    }else
    {
        ui->pushButton_6->setIcon(QIcon("C:/Users/shenmingzh/Desktop/testDATA/speaker.png"));
        voicePlayer->setVolume(voiceSlienceRecover);
        ui->verticalSlider->setValue(voiceSlienceRecover);
    }
}

void DeviceControlForm::on_tableView_2_clicked(const QModelIndex &index)
{
//    musicSelectStatus = true;
//    playType = LOCAL;
//    int nx = ui->tableView_2->currentIndex().row();//获取行

//    //ui->tableView->currentIndex().data().toString();//直接获取tableview鼠标点击位置的内容

//    QModelIndex titlemusicName = voiceLocalDataModel->index(nx,3);
//    QString path = musicPath+"/"+titlemusicName.data().toString();
//    doubleClickedMusicPath = path;
//    qDebug()<<path;
//    voicePlayer->setMedia(QUrl::fromLocalFile(path));//点击tableview获取语音
//    ui->pushButton_4->setText(QString::fromLocal8Bit("播放"));
    playAndPauseControl = false;
//    musicSelectStatus = false;

}


void DeviceControlForm::on_pushButton_2_clicked()//802c
{
    if(!connectStatus)
    {
        iMessageBox box;
        box.setMessageType("error");
        box.setMessageText(QString::fromLocal8Bit("请先连接设备!"));
        box.exec();
    }else
    {
        qDebug()<<QString::fromLocal8Bit("当前socket状态")<<socket->state();
        socket->write(this->msg->M_802C);//查询

    }

}


void DeviceControlForm::fromMainWindow(QString string)
{
    qDebug()<<"DeviceControlMMMMMMMMMMMMMMM:"<<string;
    voiceDirPath = string;
 //   emit this->toProtocolMessage(voiceDownRootDir);
   // changeVoiceRootDirFlag = true;
}

void DeviceControlForm::fromProtocolMessage(QString print_Start_Time,QString print_EndTime,QString print_Length,int record_Num)
{
    qDebug()<<QString::fromLocal8Bit("从protocol接受数据XXXXXX填充到Model中")<<print_Length;
    record_PrintCount +=1;
    tableviewModel->setItem(record_PrintCount-1,0,new QStandardItem(print_Start_Time));
    tableviewModel->setItem(record_PrintCount-1,1,new QStandardItem(print_EndTime));
    tableviewModel->setItem(record_PrintCount-1,2,new QStandardItem(print_Length));
//    tableviewModel->setItem(record_PrintCount-1,2,new QStandardItem(QString::number(record_PrintCount)));
    tableviewModel->setItem(record_PrintCount-1,3,new QStandardItem(ui->comboBox_5->currentText()));
    if(record_PrintCount == record_AllNum)
    {
        record_PrintCount = 0;
    }
}

void DeviceControlForm::fromProtocolMessageNum(int record_Num)
{
    qDebug()<<QString::fromLocal8Bit("接受查询记录条数");
    record_AllNum =record_Num;
    ui->label_16->setText(QString::number(record_Num));
}

void DeviceControlForm::PLAYMUSIC()
{
    playAndPauseControl = false;
    showDistansePlayTimeVariable = 0;
    playType = DISTENSE;
//    distensePlayTime.stop();
    distensePlayTime.start(1000);

    //清空播放缓存
    emit toProtocolMessageForToPcm2playClearPlayAllBUffer(ui->verticalSlider->value());

    ui->pushButton_4->setText(QString::fromLocal8Bit("暂停"));
    ui->horizontalSlider->setValue(0);

    qDebug()<<"+++++++++"<<PREVIndexRow<<tableview_SelectRow;
    if(PREVIndexRow !=tableview_SelectRow )//不相同
    {
        emit toProtocolMessage_2(tableview_SelectRow,PLAY,false);//获取当前索引行
        socket->write(this->msg->M_804C);
    }else
    {
        emit toProtocolMessage_2(tableview_SelectRow,PLAY,true);//获取当前索引行
    }
    ui->label_18->setText(QString::number(tableview_SelectRow+1));
    ui->label_20->setText(QString::fromLocal8Bit("在线播放"));
    PREVIndexRow = tableview_SelectRow;
}



void DeviceControlForm::DOWNLOADMUSIC()
{
    emit toProtocolMessage_2(tableview_SelectRow,DOWNLOAD,false);//获取当前索引行
    socket->write(this->msg->M_804C);
    QString theMusicFileName = ui->comboBox->currentText()+"XXX";
    writeWavHeader(theMusicFileLength,theMusicFileName);
    emit toProtocolMessageForResetCount();
}

//void DeviceControlForm::SelectStatus(const QItemSelection &selected, const QItemSelection &deselected)
//{
////    QList<QModelIndex> modelList = selected.indexes();

////    bool status = selected.contains()
//}

void DeviceControlForm::on_tableView_pressed(const QModelIndex &index)
{

    tableview_SelectRow = index.row();
    playPCM->setEnabled(true);
    downloadWAV->setEnabled(true);

    qDebug()<<QString::fromLocal8Bit("选中行4:")<<tableview_SelectRow;
}


void DeviceControlForm::fromProtocolMessageSentMusicFileLength(int second)
{
    theMusicFileLength = second;
    ui->label_11->setText(QString::number(second));
    ui->label_3->setText(QString::fromLatin1("0:00"));
    ui->horizontalSlider->setMaximum(second);
}

//远程播放的时候的进度条指示
void DeviceControlForm::showDistansePlayTime()
{

    qDebug()<<QString::fromLocal8Bit("设置远程播放的进度条");
    showDistansePlayTimeVariable +=1;
    ui->label_3->setText(QString::number(showDistansePlayTimeVariable));
    ui->horizontalSlider->setValue(showDistansePlayTimeVariable);
    if(showDistansePlayTimeVariable == theMusicFileLength)
    {
         ui->label_3->setText(QString::number(0));
        showDistansePlayTimeVariable = 0;
        ui->horizontalSlider->setValue(0);
        ui->pushButton_4->setText(QString::fromLocal8Bit("播放"));
        distensePlayTime.stop();
    }
}

void DeviceControlForm::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug()<<"DDVVV:"<<ui->verticalSlider->value();
    voicePlayer->stop();
    distanceOneMusicPlayOver = false;

//    musicSelectStatus = false;
    playAndPauseControl = false;
    iMessageBox box;
    box.setUserMessage(QString::fromLocal8Bit("播放语音!"),"prompt");
    box.setWindowTitle(QString::fromLocal8Bit("播放语音"));
//    box.removeButton((QAbstractButton*)QMessageBox::Close);
//    box.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    int boxStatus = box.exec();
//    box.buttonRole(1);

    if(boxStatus == 1)
        this->PLAYMUSIC();
    else
        box.close();
}

void DeviceControlForm::on_tableView_clicked(const QModelIndex &index)
{
    musicSelectStatus = true;
}

void DeviceControlForm::updateTableViewShow()
{
    tableviewModel->clear();
    setInitStyleTableview();
}



void DeviceControlForm::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    qDebug()<<"VVVVV:"<<ui->verticalSlider->value();
    playType = LOCAL;
    ui->label_20->setText(QString::fromLocal8Bit("本地播放"));
    ui->label_18->setText(QString::number(index.row()+1));
    ui->label_18->setAlignment(Qt::AlignCenter);
    musicSelectStatus = true;
    distensePlayTime.stop();
    QAbstractItemModel * model = const_cast<QAbstractItemModel*>(index.model());
    QString path = musicPath+"/"+model->index(index.row(),3).data().toString();
//    qDebug()<<"path:"<<doubleClickedMusicPath;
    iMessageBox box;
    box.setUserMessage(QString::fromLocal8Bit("播放语音"),"prompt");
    int status = box.exec();
    if(status = 1)
    {
        qDebug()<<"index music path:"<<path;
        voicePlayer->setMedia(QUrl::fromLocalFile(path));//点击tableview获取语音
        ui->pushButton_4->setText(QString::fromLocal8Bit("暂停"));
        playAndPauseControl = true;
        emit toProtocolMessageForToPcm2PlayStopPlay();
        int volume = ui->verticalSlider->value();
        voicePlayer->setVolume(volume);
        voicePlayer->play();
//        voicePlayer->setVolume(volume - 1);
        qDebug()<<"KKKK:"<<ui->verticalSlider->value();
        qDebug()<<QString::fromLocal8Bit("开始播放音频!");
    }
}
void DeviceControlForm::setLocalVoiceValue()
{
    ui->verticalSlider->setMaximum(100);
    ui->verticalSlider->setMinimum(0);
//    ui->verticalSlider->setValue(ui->verticalSlider->value());
}

void DeviceControlForm::fromProtocolMessageTellMusicPlayOver()
{
    qDebug()<<"Signale from ProtocolMessage!";
    distanceOneMusicPlayOver = true;
    musicSelectStatus = false;
}
//void DeviceControlForm::rebootSetVolume()
//{
//    this->readINI();
//}

//void DeviceControlForm::shutDownAppRecodVolume()
//{
//    this->writeINI();
//}

//每次关闭记录音量大小 重启读取配置
void DeviceControlForm::readINIForRebootSetVolume()
{
    QString AppPath = QCoreApplication::applicationDirPath();
    QString configIniFile = AppPath + "/config" + "/config.ini";
    QSettings settings(configIniFile,QSettings::IniFormat);

    settings.beginGroup("DistanceVolume");
    int voiceVolume = settings.value("voiceVolume").toInt();
    settings.endGroup();
    qDebug()<<"nPath"<<voiceVolume;
    ui->verticalSlider->setValue(voiceVolume);
}


void DeviceControlForm::writeINIForShutDownAppRecodVolume(int voiceVolume)
{
    QString AppPath = QCoreApplication::applicationDirPath();
    QString configIniFile = AppPath + "/config" + "/config.ini";
    qDebug()<<"configIniFile:"<<configIniFile;
    QSettings settings(configIniFile, QSettings::IniFormat);

        if(settings.isWritable())
        {
            settings.beginGroup("DistanceVolume");

            settings.setValue("voiceVolume",voiceVolume);

            settings.sync();
            settings.endGroup();
            qDebug()<<"ini_Write status:"<<settings.status();
        }

}

void DeviceControlForm::fromMainWindowForSaveInfo()
{
    writeINIForShutDownAppRecodVolume(ui->verticalSlider->value());
}



void DeviceControlForm::fromMainWindowForDeviceInfo(QString *deviceInfo)
{
    for(int i = 0;i<5;i++)
    qDebug()<<"Device:"<<deviceInfo[i];
    ui->comboBox->setCurrentText(deviceInfo[0]);
    on_comboBox_activated(deviceInfo[0]);

    ui->comboBox_2->setCurrentText(deviceInfo[1]);
    on_comboBox_2_activated(deviceInfo[1]);

    ui->comboBox_3->setCurrentText(deviceInfo[2]);
    on_comboBox_3_activated(deviceInfo[2]);

    ui->comboBox_4->setCurrentText(deviceInfo[3]);
    on_comboBox_4_activated(deviceInfo[3]);

    ui->comboBox_5->setCurrentText(deviceInfo[4]);
    on_comboBox_5_activated(deviceInfo[4]);


}
