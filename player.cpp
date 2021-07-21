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
    QString reqname = QRegularExpression("[^/]*.mp3").match(q->CompleteName()).captured(0).replace(".mp3","");
    info->name = q->Title().isEmpty() ? reqname : q->Title();
    info->des = q->CompleteName();

    delete q;
    return info;
}
void player::addMusic(QString filePath){
    int flag = musicList.length();
    playInfo *info = getInf(filePath);
    varplaylist->addMedia(QUrl::fromLocalFile(filePath));
    musicList.append(info);
    if(flag == 0){//增加之前是空
        setIndex(0);
    }
    //varplaylist->
    emit listChange();
}
void player::addMusic(QString filePath, int index){
    int flag = musicList.length();
    playInfo *info = getInf(filePath);
    musicList.insert(index,info);
    varplaylist->insertMedia(index, QUrl::fromLocalFile(filePath));
    if(flag == 0){//增加之前是空
        setIndex(0);
    }
    emit listChange();
}
void player::addOlMusic(QString id ,QString name,QString author,QString url1,QString url2,QString duration,QString album){
    //qDebug() << url1;
    int flag = musicList.length();
    playInfo *info = new playInfo;
    info->id = id;
    info->name = name;
    info->Author = author;
    info->url1 = url1;
    info->url2 = url2;
    info->duration = duration;
    info->album = album;
    info->des = name;
    info->isOl = true;
    info->mp3 = false;
    info->lrc = false;
    fileproce *f = new fileproce;
    downFile *d1 = new downFile;
    connect(d1,SIGNAL(success(QString,int)),this,SLOT(downSucc(QString,int)));

    downFile *d2 = new downFile;
    connect(d2,SIGNAL(success(QString,int)),this,SLOT(downSucc(QString,int)));
    if( !f->exist(QString("cache/%1.mp3").arg(id)) ){
        //歌曲缓存不存在
        d1->down(url1,id,1);
    }else{
        info->mp3 = true;
        info->filePath = QString("cache/%1.mp3").arg(id);
    }
    if( !f->exist(QString("cache/%1.lrc").arg(id)) ){
        //歌词缓存不存在
        d2->down(url2,id,2);
    }else{
        info->lrc = true;
    }
    musicList.append(info);

    varplaylist->addMedia(QUrl::fromLocalFile( QString("cache/%1.mp3").arg(id) ));
    if(flag == 0){//增加之前是空
        setIndex(0);
    }
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
    //Online拦截
    if( musicList.at(index)->isOl ){
        //在线歌曲
        if( !musicList.at(index)->lrc || !musicList.at(index)->mp3){
            //当 MP3 或 lrc 不存在的时候 开启缓存动画
            emit musicLoading();
            //QTimer *pTimer = new QTimer(this);
            prePlayerIndex = index;
            QTimer::singleShot( 3000, this, SLOT(hideLoading()) );
            qDebug() << musicList.at(index)->isOl << musicList.at(index)->lrc << musicList.at(index)->mp3;
            return;
        }
    }

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


void player::downSucc(QString id,int type){
    qDebug() << id << "&" << type;
    if(type == 1){
        for(int i=0;i<musicList.length();i++){
            if(musicList.at(i)->id == id){
                musicList.at(i)->mp3 = true;
                musicList.at(i)->filePath = QString("cache/%1.mp3").arg(id);
                qDebug() << musicList.at(i)->filePath;
                break;
            }
        }
    }else if(type == 2){
        for(int i=0;i<musicList.length();i++){
            if(musicList.at(i)->id == id){
                musicList.at(i)->lrc = true;
                break;
            }
        }
    }
}

void player::hideLoading(){
    //加载完成
    emit musicHideLoading();
    qDebug() << "hideLoading";
    varplaylist->setCurrentIndex(prePlayerIndex);
    varplay->play();
}
