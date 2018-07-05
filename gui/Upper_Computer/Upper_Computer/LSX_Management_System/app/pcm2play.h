#ifndef PCM2PLAY_H
#define PCM2PLAY_H
#include <QAudioOutput>
#include <QTimer>
#include <QByteArray>



class pcm2play:public QObject
{
    Q_OBJECT
public:
    pcm2play(QObject * parent = 0);
    void initlayer();
//    int GetAudioOutputVolumn_Win7(const std::string &deviceName);

signals:
    void toProtocolMessageSameMusicLangth(int len);
    void toProtocolMessageMusicPlayOver();
public slots:
    void slotTimeout(char *fileBuffer, int len);
    void playPCM();
    void fromProtocolMessageForPlayOrPauseControl(bool type);
    void fromProtocolMessageForClearAllBuffer(int volume);
    void fromProtocolMessageReceiveOver();
    void fromProtocolMessageSameSelectPlay(bool);
    void fromProtocolMessageForStopDistancePlay();
    void fromProtocolMessageForChangeVolume(int volume);//set distance volume . 信号过来的是0-100,QAudioOutput处理的是0.0-1.0


public:
    QByteArray tempBuffer;


private:
    QByteArray musicBuffer;
    int fileLength;
    QAudioOutput* audioOutput;

    QIODevice * streamOut;
    QTimer * playTimer;

    int nowPlayPositon;


    int TestPlayCount;
    bool SameSelectPlay;
    qreal nowVolume;
    ;

};

#endif // PCM2PLAY_H
