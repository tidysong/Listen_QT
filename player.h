#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QObject>
#include <QTimer>
#include <qmediainfo.h>
#include <fileproce.h>
#include <downfile.h>
class playInfo{
    public:
        QString filePath;
        QString name;
        QString Author;
        QString duration;

        QString des;

        QString id;
        QString album;
        QString url1;//mp3
        QString url2;//lrc
        bool isOl;//是否为在线歌曲
        bool mp3,lrc;
};
class player : public QObject
{
    Q_OBJECT
public:
    explicit player(QObject *parent = nullptr);
    void initConfig();//初始化配置
    void addMusic(QString filePath);//添加歌曲到末尾
    void addMusic(QString filePath, int index);//指定位置
    void play();//播放
    void pause();//暂停
    void setIndex(int index);
    void next();
    void pre();
    void remove(int index);
    void clear();
    void setPosition(qint64 position);
    void setVol(int position);
    void addOlMusic(QString id ,QString name,QString author,QString url1,QString url2,QString duration,QString album);//网络歌曲
    QString exp(QString text, QString g);
    playInfo* getInf(QString filePath);
    static player *p;
    QList<playInfo*> musicList;//歌单列表
    QMediaPlayer *varplay;
    QMediaPlaylist *varplaylist;
    int prePlayerIndex = 0;
signals:

    void MediaChanged(const QMediaContent &content);
    void PositionChanged(qint64 duration);
    void DurationChanged(qint64 duration);
    void stateChange(QMediaPlayer::State newState);
    void listChange();//播放列表变化
    void IndexChanged(int position);
    void volumeChange(int volume);//音量变化
    void modeChange(QMediaPlaylist::PlaybackMode mode);
    void musicHideLoading();
    void musicLoading();
private slots:
    void currentMediaChanged(const QMediaContent &content);
    void currentIndexChanged(int position);
    void updatePosition(qint64 duration);
    void updateDuration(qint64 duration);
    void stateChanged(QMediaPlayer::State newState);
    void volumeChanged(int volume);
    void playbackModeChanged(QMediaPlaylist::PlaybackMode);

    void downSucc(QString, int type);
    void hideLoading();
};

#endif // PLAYER_H
