#include "pcm2play.h"
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <Windows.h>

pcm2play::pcm2play(QObject *parent)
{
    nowPlayPositon = 0;
    TestPlayCount = 0;
    nowVolume = 0;
    playTimer  = new QTimer;
    connect(playTimer,&QTimer::timeout,this,&pcm2play::playPCM);


}


void pcm2play::initlayer()
{
    //设置采样格式
    QAudioFormat audioFormat;
    //设置采样率
    audioFormat.setSampleRate(8000);
    //设置通道数
    audioFormat.setChannelCount(1);
    //设置采样大小，一般为8位或16位
    audioFormat.setSampleSize(16);
    //设置编码方式
    audioFormat.setCodec("audio/pcm");
    //设置字节序
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    //设置样本数据类型
    audioFormat.setSampleType(QAudioFormat::UnSignedInt);
    //音频设备信息
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
    if (!info.isFormatSupported(audioFormat))
    {
        qDebug()<<"default format not supported try to use nearest";
        audioFormat = info.nearestFormat(audioFormat);
    }
    audioOutput = new QAudioOutput(audioFormat);
//    audioOutput->setVolume(0.30);//可以设置应用的播放音量只要关联到 音量控制器上 就好了

//    //定时器
//    timer=new QTimer(this);
//    connect(timer, SIGNAL(timeout()), SLOT(slotTimeout()));
}

void pcm2play::slotTimeout(char*pcmBuffer,int len)
{
    qDebug()<<"This is test Play";
    static int i=0;
    TestPlayCount +=len;
    qDebug()<<QString::fromLocal8Bit("信号带过来的信息:")<<pcmBuffer;
    qDebug()<<QString::fromLocal8Bit("QByteArray(pcmBuffer:)")<<QByteArray(pcmBuffer);
    qDebug()<<QString::fromLocal8Bit("pcmBufferSize:")<<QByteArray(pcmBuffer).length();
    qDebug()<<"TestPlayCount："<<TestPlayCount;
    //    QFile F("C:/Users/shenmingzh/Desktop/testDATA/ABCD.wav");
//    F.open(QIODevice::Append);

//    int iCount = F.write((char*)pcmBuffer,len);
//    qDebug()<<QString::fromLocal8Bit("写入计数ii:")<<iCount;
//    F.close();


        musicBuffer = musicBuffer.append(pcmBuffer,len);//循环播放用该buffer，每次更改清空就行
        tempBuffer = tempBuffer.append(pcmBuffer,len);//tempBuffer 流缓存 一边存 量到了 就取走  //现在修改为固定缓存区
        fileLength = tempBuffer.length();
        qDebug()<<QString::fromLocal8Bit("播放类中fileLength:")<<fileLength;



}




void pcm2play::playPCM()
{

    if(audioOutput&&audioOutput->state()!=QAudio::StoppedState&&audioOutput->state()!=QAudio::SuspendedState)
    {
        int chunks = audioOutput->bytesFree()/audioOutput->periodSize();//audio 可用字节/每一帧字节   可用数据块
        while (chunks)
       {
           if (tempBuffer.length() >= audioOutput->periodSize())//如果源文件长度大于单帧的长度，每次写入一帧的大小
           {
               //写入到扬声器
//                    qDebug()<<QString::fromLocal8Bit("语音播放");
               streamOut->write(tempBuffer.data(),audioOutput->periodSize());
//               qDebug()<<"streamOut->bytesAvailable"<<streamOut->bytesAvailable()<<streamOut->size()<<streamOut->bytesToWrite();
               nowPlayPositon = nowPlayPositon+audioOutput->periodSize();
//               qDebug()<<"nowPlayPositon:"<<nowPlayPositon;
               tempBuffer = tempBuffer.mid(audioOutput->periodSize());
           }
           else//如果文件总长度小于一帧的长度，直接一次写入所有的数据
           {
               //写入到扬声器
               streamOut->write(tempBuffer);
               nowPlayPositon = nowPlayPositon +tempBuffer.size();
               tempBuffer.clear();//一次播放完清空temp缓存器
//               qDebug()<<"Last nowPlayPositon:"<<nowPlayPositon;
//               qDebug()<<"musicBuffer:"<<musicBuffer.length();
//               --chunks;
               break;
           }
//           qDebug()<<"chunks;"<<chunks;
           --chunks;
        }
        if(nowPlayPositon == musicBuffer.length() && nowPlayPositon > 0)
        {
            qDebug()<<"musicBuffer.length():"<<musicBuffer.length();
//            musicBuffer.clear();
            playTimer->stop();
            emit toProtocolMessageMusicPlayOver();
        }
    }
}

void pcm2play::fromProtocolMessageForPlayOrPauseControl(bool type)
{
    if(type)//true 是播放
    {
        playTimer->start();
        audioOutput->start();
//        qDebug()<<QString::fromLocal8Bit("当前音量:")<<audioOutput->volume();
    }
    else
    {
        qDebug()<<QString::fromLocal8Bit("暂停位置:")<<nowPlayPositon;
        qDebug()<<QString::fromLocal8Bit("固定缓冲区大小:")<<musicBuffer.length();//固定缓冲区大小要从 Protocolmessage虫传送过来，传送中点击暂停pcm2play绘停止导致固定缓冲区数据不全

        playTimer->stop();
//        audioOutput->stop();
    }
}

void pcm2play::fromProtocolMessageForClearAllBuffer(int volume)//重新选择后播放 远程播放（选择不同的时候的）
{
        nowPlayPositon = 0;
        TestPlayCount = 0;
        playTimer->start();   
        audioOutput->setVolume(volume);
        streamOut = audioOutput->start();
//        audioOutput->setVolume(1);
       qDebug()<<QString::fromLocal8Bit("音频类别:")<<audioOutput->category();
//        audioOutput->
       qDebug()<<QString::fromLocal8Bit("设置完后的音量:")<<nowVolume;
       qDebug()<<QString::fromLocal8Bit("声音音量:")<<audioOutput->volume();

}

void pcm2play::fromProtocolMessageReceiveOver()//807信号过来通知806语音传送结束
{
    qDebug()<<QString::fromLocal8Bit("语音文件传送结束");
//    playTimer->start();
//    streamOut = audioOutput->start();
    //    playTimer->stop();
}

void pcm2play::fromProtocolMessageSameSelectPlay(bool sameOrNot)
{
    qDebug()<<"KKKKKKKKKKKKKKKKKKKK"<<sameOrNot;
//   SameSelectPlay = sameOrNot;
   if(sameOrNot)//两次相同
   {
       qDebug()<<"ALL SAME";
        tempBuffer = musicBuffer;
        emit toProtocolMessageSameMusicLangth(tempBuffer.length());
        playTimer->start();
   }else
   {
       //clear Buffer
       tempBuffer.clear();
       musicBuffer.clear();
       qDebug()<<"clear musicBuffer:";
   }
}

void pcm2play::fromProtocolMessageForStopDistancePlay()
{
        playTimer->stop();
        audioOutput->setVolume(1);
}

void pcm2play::fromProtocolMessageForChangeVolume(int volume)
{
    nowVolume = qreal(volume)/100;
    qDebug()<<"Now Volume:"<<nowVolume;
    audioOutput->setVolume(nowVolume);
}


//int pcm2play::GetAudioOutputVolumn_Win7(const std::string &deviceName)
//{
//    MMRESULT          rc;     // 多媒体函数返回结果变量
//    HMIXER            hMixer; // 混合器设备句柄
//    MIXERLINE         mxl;    // 音频线路标准状态信息结构体
//    MIXERLINECONTROLS mxlc;   // 音频线路控制器集合信息结构体
//    MIXERCONTROL      mxc;    // 单个音频线路控制器信息结构体

//    // 打开混合器设备
//    rc = mixerOpen(&hMixer, // 返回的设备句柄
//        0,       // 单声卡的设备ID为零
//        0,       // 不使用回调机制
//        0,       // 回调函数参数
//        0);      // MIXER_OBJECTF_MIXER宏的值，表示任选有效设备ID

//    // 打开混合器设备无错的话，则
//    if (MMSYSERR_NOERROR == rc)
//    {
//        // MIXERLINE 结构体变量清零
//        ZeroMemory(&mxl, sizeof(MIXERLINE));

//        mxl.cbStruct = sizeof(MIXERLINE); // 微软用此办法判断版本
//        // 指出需要获取的通道，声卡的音频输出用MIXERLINE_COMPONENTTYPE_DST_SPEAKERS
//        mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;

//        // 取得混合器设备的指定线路信息
//        rc = mixerGetLineInfo((HMIXEROBJ)hMixer,
//            &mxl,
//            // 取得MIXERLINE::dwComponentType指定类型的第一个音频线路信息
//            MIXER_GETLINEINFOF_COMPONENTTYPE);

//        // 取得混合器设备的指定线路信息成功的话，则
//        if (MMSYSERR_NOERROR == rc)
//        {
//            // MIXERCONTROL 结构体变量清零
//            ZeroMemory(&mxc, sizeof(MIXERCONTROL));

//            mxc.cbStruct = sizeof(mxc); // 微软用此办法判断版本

//            // MIXERLINECONTROLS 结构体变量清零
//            ZeroMemory(&mxlc, sizeof(MIXERLINECONTROLS));

//            mxlc.cbStruct = sizeof(mxlc); // 微软用此办法判断版本

//            mxlc.dwLineID = mxl.dwLineID; // 上面取得的声卡音频输出线路标识
//            // 控制类型为控制音量
//            mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
//            mxlc.cControls = 1;          // 使用 MIXERCONTROL 结构体变量个数
//            mxlc.pamxctrl = &mxc;        // MIXERCONTROL 结构体变量指针
//            mxlc.cbmxctrl = sizeof(mxc); // MIXERCONTROL 结构体变量字节大小

//            // 取得控制器信息
//            rc = mixerGetLineControls((HMIXEROBJ)hMixer,
//                &mxlc,
//                MIXER_GETLINECONTROLSF_ONEBYTYPE);

//            // 取得控制器信息成功的话，则
//            if (MMSYSERR_NOERROR == rc)
//            {
//                // 获取控制器中的值的音量范围：mxc.Bounds.lMinimum到mxc.Bounds.lMaximum.
//                MIXERCONTROLDETAILS        mxcd;      // 控制器的状态信息
//                MIXERCONTROLDETAILS_SIGNED volStruct; // 音量结构体变量(就一个成员量)

//                // MIXERCONTROLDETAILS 结构体变量清零
//                ZeroMemory(&mxcd, sizeof(mxcd));

//                mxcd.cbStruct = sizeof(mxcd);       // 微软用此办法判断版本
//                mxcd.dwControlID = mxc.dwControlID; // 上面取得的控制器标识
//                mxcd.paDetails = &volStruct;        // 音量结构体变量指针
//                mxcd.cbDetails = sizeof(volStruct); // 音量结构体变量字节大小
//                mxcd.cChannels = 1;                 // 取得或设置全部通道

//                //  获取控制器中的值的音量范围：mxc.Bounds.lMinimum到mxc.Bounds.lMaximum.

//                // 获得音量值
//                rc = mixerGetControlDetails((HMIXEROBJ)hMixer,
//                    &mxcd,
//                    MIXER_GETCONTROLDETAILSF_VALUE);

//                if (MMSYSERR_NOERROR == rc)
//                {
//                    long step = ( mxc.Bounds.lMaximum - mxc.Bounds.lMinimum ) /100;

//                    int index = ( volStruct.lValue - mxc.Bounds.lMinimum) /step ;
//                    printf("音量：%X", volStruct.lValue);
//                    return index;
//                }
//            }
//        }
//    }
//}

