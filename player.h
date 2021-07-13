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
#include <qmediainfo.h>
class playInfo{
    public:
        QString filePath;
        QString name;
        QString Author;
        QString duration;
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
    void move(int index);
    void clear();
    void setPosition(qint64 position);
    void setVol(int position);
    QString exp(QString text, QString g);
    playInfo* getInf(QString filePath);
    static player *p;
    QList<playInfo*> musicList;//歌单列表
    QMediaPlayer *varplay;
    QMediaPlaylist *varplaylist;
signals:

    void MediaChanged(const QMediaContent &content);
    void IndexChanged(int position);
    void PositionChanged(qint64 duration);
    void DurationChanged(qint64 duration);
    void stateChange(QMediaPlayer::State newState);
    void listChange();//播放列表变化
    void volumeChange(int volume);//音量变化
private slots:
    void currentMediaChanged(const QMediaContent &content);
    void currentIndexChanged(int position);
    void updatePosition(qint64 duration);
    void updateDuration(qint64 duration);
    void stateChanged(QMediaPlayer::State newState);
    void volumeChanged(int volume);
};

#endif // PLAYER_H
