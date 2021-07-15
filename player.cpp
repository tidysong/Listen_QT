#include "player.h"

player *player::p = new player;
player::player(QObject *parent) : QObject(parent)
{
    varplaylist = new QMediaPlaylist;
    varplay = new QMediaPlayer;
    varplay->setPlaylist(varplaylist);
    initConfig();
    connect(varplaylist,SIGNAL(currentMediaChanged(const QMediaContent&)),this,SLOT(currentMediaChanged(const QMediaContent&)));//切歌
    connect(varplaylist,SIGNAL(currentIndexChanged(int)),this,SLOT(currentIndexChanged(int)));

    connect(varplay, SIGNAL(positionChanged(qint64)), this,SLOT(updatePosition(qint64)));//进度改变
    connect(varplay, SIGNAL(durationChanged(qint64)), this, SLOT(updateDuration(qint64)));//时长改变
    connect(varplay, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));//播放状态改变

    connect(varplay, SIGNAL(volumeChanged(int)), this, SLOT(volumeChanged(int)));//音量改变
    connect(varplaylist, SIGNAL(playbackModeChanged(QMediaPlaylist::PlaybackMode)), this, SLOT(playbackModeChanged(QMediaPlaylist::PlaybackMode)));//播放模式改变

}
void player::initConfig(){
    varplay->setVolume(50);//设置音量
    varplaylist->setPlaybackMode(QMediaPlaylist::Loop);//循环方式
}

playInfo* player::getInf(QString filePath){
    qDebug() << filePath;
    QMediaInfo *q = new QMediaInfo;
    q->Open(filePath);
    playInfo *info = new playInfo();
    info->filePath = filePath;
    info->duration = QRegularExpression("[0-9]{2}:[0-9]{2}:[0-9]{2}").match(q->Duration()).captured(0).mid(3);
    QString a = q->Inform();
    a.replace(QRegularExpression("\\s"),"&");
    QRegularExpression re("Performer(&)+:(&)+.*?&");
    a = re.match(a).captured(0);
    a.remove("&");a.remove("Performer:");
    if(a.isEmpty()){
        info->Author = "未知歌手";
    }else{
        info->Author = a;
    }
    info->name = q->Title().isEmpty() ? q->CompleteName() : q->Title();
    delete q;
    return info;
}
void player::addMusic(QString filePath){
    playInfo *info = getInf(filePath);
    musicList.append(info);
    varplaylist->addMedia(QUrl::fromLocalFile(filePath));
    emit listChange();
}
void player::addMusic(QString filePath, int index){
    playInfo *info = getInf(filePath);
    musicList.insert(index,info);
    varplaylist->insertMedia(index, QUrl::fromLocalFile(filePath));
    emit listChange();
}
void player::setVol(int position){
    varplay->setVolume(position);
}
void player::play(){
    varplay->play();
}
void player::pause(){
    varplay->pause();
}
void player::next(){
    varplaylist->next();
}

void player::pre(){
    varplaylist->previous();
}
void player::setIndex(int index){
    varplaylist->setCurrentIndex(index);
}
void player::remove(int index){
    varplaylist->removeMedia(index);
    musicList.removeAt(index);
    emit listChange();
}
void player::clear(){
    varplaylist->clear();
}
void player::setPosition(qint64 position){
    varplay->setPosition(position);
}
//SIGNAL
void player::currentIndexChanged(int position){
    //跳至上 下一首歌 或 播放列表改变
    emit IndexChanged(position);
}
void player::currentMediaChanged(const QMediaContent &content){
    //跳至上 下一首歌
    emit MediaChanged(content);
}
void player::updatePosition(qint64 duration){
    emit PositionChanged(duration);
}
void player::updateDuration(qint64 duration){
    emit DurationChanged(duration);
}
void player::stateChanged(QMediaPlayer::State newState){
    emit stateChange(newState);
}

void player::volumeChanged(int position){
    emit volumeChange(position);
}


void player::playbackModeChanged(QMediaPlaylist::PlaybackMode mode){
    emit modeChange(mode);
}
